/*
 * user_model.c
 *
 *  Created on: 17 Jun 2026
 *      Author: mOffice
 */

#include "user_model.h"
#include <math.h>
#include "XCU_UDSonly.h"   /* rtB.inhibitDrive from the template UDS model */
#include "powertrain.h"

/* CAN2 is Marc's UDS bus. IDs 0x123 and 0x124 come from outside this
 * application and must not be reused. The template example traffic on 0x123,
 * 0x124 and 0x125 was removed (it sent uninitialised bytes and let a CAN2
 * frame drive digital output 1). Do not add application traffic to CAN2. */

/* --- ERR2081 coolant temperature sensor (Stage 1) -------------------------
 * Physical: pin C7 (AN INPUT 3) -> anInputExternal3, per
 *           Defender_VCU_xCU_Mapping_updated.xlsx ("xCU Pin Mapping" sheet).
 * CAN:      DBC "Engine_Temps1" (ID 0x110 / BO_ 272), CoolantTemp signal,
 *           bits 0-15, int16 little-endian, scale 0.1 degC, on CAN1
 *           (confirmed Stage 1 sensor-logging bus, NOT CAN2 which is
 *           Marc's UDS bootloader bus - do not repurpose).
 *
 * TODO CONFIRM WITH MARC/EVPARTS before trusting readings from this channel:
 *  - Pull-up resistor value + supply rail for the C7/C8 divider. EVPDOC1242's
 *    12.890625 mV/bit (150k:10k divider, 3.3V ref) scaling is documented only
 *    for the DEDICATED 50V analog inputs (C5/C6/B6-B10). C7-C10 are the
 *    "selectable digital/analog, 30V max" channels, and the mapping sheet
 *    explicitly flags coolant/oil/gearbox temp inputs "Confirm" for exactly
 *    this reason - it is not known whether the same divider is stuffed on
 *    C7. The values below (1k pull-up to +5V) are a placeholder only,
 *    matching the fuel sender pattern used elsewhere in this project.
 *  - NTC resistance/temperature curve. Fitted (single Beta equation) from
 *    public parts-listing data points (~2-3 kOhm @25C from the VCU Sensor
 *    Reference sheet, ~28 kOhm @-30C / ~300 Ohm @85C / ~90 Ohm @130C from
 *    Land Rover parts documentation) - NOT sourced from an EVParts/JLR
 *    datasheet. Verify against the RAVE manual or a bench test (ice water /
 *    boiling water) before relying on it for anything safety related.
 */
#define COOLANT_PULLUP_OHMS        1000.0f   /* TODO CONFIRM - placeholder */
#define COOLANT_SUPPLY_V           5.0f      /* TODO CONFIRM - assumes pull-up to regulated +5V (pin B1) */
#define COOLANT_ADC_MV_PER_BIT     12.890625f /* per EVPDOC1242 - confirmed only for dedicated 50V inputs, TODO CONFIRM applies to C7 */

#define COOLANT_NTC_R0_OHMS        28000.0f  /* resistance at COOLANT_NTC_T0_K - fitted from public data, TODO CONFIRM */
#define COOLANT_NTC_T0_K           243.15f   /* -30 degC in Kelvin */
#define COOLANT_NTC_BETA           3434.6f   /* Beta coefficient fitted from -30/85/130 degC reference points - TODO CONFIRM */
#define KELVIN_TO_CELSIUS_OFFSET   273.15f

#define COOLANT_TEMP_FAULT_RAW     0x7FFF    /* "not fitted"/fault placeholder - 3276.7 degC, clearly outside the -40..200 DBC range */

#define ENGINE_TEMPS1_ID           0x110U    /* per Defender_DBC_v1.txt: BO_ 272 Engine_Temps1 */

/* --- Fuel level sender (Stage 1) -------------------------------------------
 * Physical: pin B7 (AN INPUT 8) -> anInputExternal8. B7 is a DEDICATED 50V
 *           analog input (CONFIRMED 150k:10k / 3.3V-ref divider per
 *           EVPDOC1242 / "xCU Pin Allocation" sheet) - unlike the coolant
 *           sensor on C7, the raw-ADC-to-pin-voltage conversion here is
 *           trusted. NOTE: B7 was previously shown allocated to Oil pressure
 *           in Defender_VCU_xCU_Mapping_updated.xlsx - that sheet is being
 *           updated alongside this change to move Oil pressure off B7
 *           pending a new pin decision. Don't wire Oil pressure to B7.
 * Circuit:  1k pull-up to ignition-switched +12V -> node (read by B7) ->
 *           resistive fuel sender -> GND. (established in earlier design
 *           work - verify against the physical loom, not yet bench-checked.)
 *           The pull-up is fed from the SAME ignition-switched rail that
 *           powers the xCU itself (LV+ input, C1/C2), so the rail's real
 *           voltage is measured live via anLvSupply (analog input 12)
 *           instead of assuming a fixed 12V - the alternator can hold this
 *           rail at 13.5-14.5V running, or well under 12V while cranking,
 *           and a fixed-12V assumption would bias every reading.
 * Cal:      Liters = -0.2691 * OhmsSender + 44.719 (Red-supplied linear fit)
 * CAN:      DBC "Fuel_Status" (ID 0x301 / BO_ 769), on CAN1, buffer 2.
 */
#define FUEL_PULLUP_OHMS           1000.0f    /* established design value - verify against loom */
#define FUEL_SUPPLY_MIN_V          10.0f      /* xCU minimum operating supply per EVPDOC1242 - below this, treat anLvSupply as invalid rather than divide by a near-zero/garbage rail */
#define FUEL_ADC_MV_PER_BIT        12.890625f /* per EVPDOC1242 - CONFIRMED for this dedicated 50V pin */

#define FUEL_CAL_SLOPE_L_PER_OHM   (-0.2691f) /* Red's calibration: Liters = slope*Ohms + offset */
#define FUEL_CAL_OFFSET_L          44.719f

#define FUEL_LEVEL_MAX_L           50.0f      /* Fuel_Status.FuelLevel_L DBC valid range is 0-50L */
#define FUEL_LOW_WARN_L            5.0f       /* placeholder low-fuel threshold - tune to taste */

#define FUEL_LEVEL_FAULT_RAW       0xFFFFU    /* "not available"/fault placeholder for the unsigned 16-bit signals */
#define FUEL_STATUS_ID             0x301U     /* per Defender_DBC_v1.txt: BO_ 769 Fuel_Status */

/* --- Node heartbeat / bus health (Stage 1) ---------------------------------
 * CAN: DBC "Node_Heartbeat" (ID 0x3F0 / BO_ 1008), on CAN1. Broadcasts this
 *      xCU's identity, firmware version, live supply rail voltage, and a
 *      rolling counter other nodes can use to confirm it's still alive.
 * No project-wide NodeID or firmware-versioning scheme exists yet, so
 * NodeID/SW_Major/SW_Minor below are placeholders - update once you have
 * real values. FaultCount/LastFaultCode are placeholders too, since there's
 * no fault-tracking system implemented in user_model_code yet.
 */
#define NODE_HEARTBEAT_ID          0x3F0U   /* per Defender_DBC_v1.txt: BO_ 1008 Node_Heartbeat */
#define HEARTBEAT_NODE_ID          0U       /* placeholder - represents this xCU's ENG_NODE role */
#define HEARTBEAT_SW_MAJOR         0U       /* placeholder firmware version - bump when you adopt real versioning */
#define HEARTBEAT_SW_MINOR         1U
/* FaultCount and LastFaultCode come from the powertrain fault manager (fault_mgr.h).
 * LastFaultCode is FaultId + 1, 0 = none. */


/* user model functions */
/* average the ADC_SAMPLE_COUNT raw samples for one analog channel to reduce noise */
static unsigned int averageAdcSamples(const unsigned int *samples, unsigned int count){
    unsigned int i;
    unsigned int sum = 0U;
    for (i = 0U; i < count; i++){
        sum += samples[i];
    }
    return (sum / count);
}

/* convert a raw averaged ADC count on the coolant temp channel (C7 / anInputExternal3)
 * to a DBC-ready int16 value in units of 0.1 degC (Engine_Temps1.CoolantTemp scale).
 * Returns COOLANT_TEMP_FAULT_RAW if the sensor reads as open or shorted, or the
 * computed temperature falls outside the DBC signal's valid range.
 * See the TODO CONFIRM notes above the #defines before trusting this reading. */
static short coolantTempRaw0p1C(unsigned int adcCountAvg){
    float vPin;
    float rNtc;
    float tempKelvin;
    float tempCelsius;
    int   rawSigned;

    vPin = ((float)adcCountAvg * COOLANT_ADC_MV_PER_BIT) / 1000.0f; /* volts at the ADC pin */

    /* guard against divide-by-zero / implausible readings (open or shorted sensor) */
    if ((vPin <= 0.05f) || (vPin >= (COOLANT_SUPPLY_V - 0.05f))){
        return (short)COOLANT_TEMP_FAULT_RAW;
    }

    /* circuit: COOLANT_SUPPLY_V -> pull-up -> node (vPin, measured by ADC) -> NTC -> GND */
    rNtc = COOLANT_PULLUP_OHMS * vPin / (COOLANT_SUPPLY_V - vPin);

    /* Beta equation: 1/T = 1/T0 + (1/B)*ln(R/R0) */
    tempKelvin  = 1.0f / ((1.0f / COOLANT_NTC_T0_K) + (logf(rNtc / COOLANT_NTC_R0_OHMS) / COOLANT_NTC_BETA));
    tempCelsius = tempKelvin - KELVIN_TO_CELSIUS_OFFSET;

    /* Engine_Temps1.CoolantTemp valid range per Defender_DBC_v1.txt is -40 to 200 degC */
    if ((tempCelsius < -40.0f) || (tempCelsius > 200.0f)){
        return (short)COOLANT_TEMP_FAULT_RAW;
    }

    rawSigned = (int)(tempCelsius * 10.0f + ((tempCelsius >= 0.0f) ? 0.5f : -0.5f)); /* round to nearest 0.1 degC */
    return (short)rawSigned;
}

/* pack CAN1 "Engine_Temps1" (ID 0x110) frame per Defender_DBC_v1.txt.
 * Only CoolantTemp is wired up in Stage 1 - the other three signals in this
 * frame (CrankcaseTemp, IAT_PostIC, AmbientTemp) are sent as the "not fitted"
 * placeholder until those sensors are added to the loom. */
CAN_MESSAGE_BUS packEngineTemps1MSG(ANALOG_INPUT_BUS data){
    CAN_MESSAGE_BUS packedData;
    unsigned int coolantAdcAvg;
    short coolantRaw;
    short crankcaseRaw = (short)COOLANT_TEMP_FAULT_RAW; /* not fitted yet */
    short iatRaw       = (short)COOLANT_TEMP_FAULT_RAW; /* not fitted yet */
    short ambientRaw   = (short)COOLANT_TEMP_FAULT_RAW; /* not fitted yet */

    coolantAdcAvg = averageAdcSamples(data.anInputExternal3, ADC_SAMPLE_COUNT);
    coolantRaw    = coolantTempRaw0p1C(coolantAdcAvg);

    packedData.ID = ENGINE_TEMPS1_ID;
    packedData.Length = 0x08U;
    packedData.Extended = 0x00U;

    packedData.Data[0] = (unsigned char)(coolantRaw & 0xFF);
    packedData.Data[1] = (unsigned char)((coolantRaw >> 8) & 0xFF);
    packedData.Data[2] = (unsigned char)(crankcaseRaw & 0xFF);
    packedData.Data[3] = (unsigned char)((crankcaseRaw >> 8) & 0xFF);
    packedData.Data[4] = (unsigned char)(iatRaw & 0xFF);
    packedData.Data[5] = (unsigned char)((iatRaw >> 8) & 0xFF);
    packedData.Data[6] = (unsigned char)(ambientRaw & 0xFF);
    packedData.Data[7] = (unsigned char)((ambientRaw >> 8) & 0xFF);

    return packedData;
}

/* raw averaged ADC count on the xCU's own LV supply channel (anLvSupply) ->
 * rail voltage in volts. Generic (not fuel-specific) despite living in this
 * section - reused below for the Node_Heartbeat SupplyV signal too. The
 * fuel sender pull-up shares this same rail, so this also stands in for a
 * fixed "assume 12V" constant there - it tracks the real alternator/cranking
 * swing instead of being biased by it. */
static float lvSupplyVolts(unsigned int lvAdcCountAvg){
    return ((float)lvAdcCountAvg * FUEL_ADC_MV_PER_BIT) / 1000.0f;
}

/* true if the fuel sender channel reads as an open circuit (broken/disconnected
 * wire) - node pulled almost all the way up to the (measured) pull-up rail. */
static unsigned char fuelIsOpenCircuit(float vNode, float supplyV){
    return (vNode >= (supplyV * 0.95f)) ? 1U : 0U;
}

/* raw averaged ADC count on the fuel sender channel (B7 / anInputExternal8),
 * plus the LIVE measured supply rail voltage (see lvSupplyVolts) ->
 * sender resistance in ohms. Returns -1.0f if an open circuit is detected,
 * or if the supply reading itself looks invalid (below FUEL_SUPPLY_MIN_V).
 * Note: a shorted sender (0 ohm) is not distinguishable from a normal
 * "tank full" reading with this simple divider - only open circuit is
 * flagged as an unambiguous fault. */
static float fuelSenderOhms(unsigned int adcCountAvg, float supplyV){
    float vNode;
    float ohms;

    if (supplyV < FUEL_SUPPLY_MIN_V){
        return -1.0f; /* LV rail reading itself is implausible - don't trust the divider math */
    }

    vNode = ((float)adcCountAvg * FUEL_ADC_MV_PER_BIT) / 1000.0f;

    if (fuelIsOpenCircuit(vNode, supplyV)){
        return -1.0f;
    }

    ohms = FUEL_PULLUP_OHMS * vNode / (supplyV - vNode);
    if (ohms < 0.0f){
        ohms = 0.0f; /* clamp small negative results from ADC noise near a full tank */
    }
    return ohms;
}

/* sender resistance (ohms) -> fuel level (liters), using Red's linear
 * calibration fit. Clamped to the Fuel_Status.FuelLevel_L DBC valid range.
 * Returns -1.0f (fault, propagated from fuelSenderOhms) unchanged. */
static float fuelLevelLiters(float ohms){
    float liters;

    if (ohms < 0.0f){
        return -1.0f;
    }

    liters = (FUEL_CAL_SLOPE_L_PER_OHM * ohms) + FUEL_CAL_OFFSET_L;
    if (liters < 0.0f){
        liters = 0.0f;
    }
    if (liters > FUEL_LEVEL_MAX_L){
        liters = FUEL_LEVEL_MAX_L;
    }
    return liters;
}

/* pack CAN1 "Fuel_Status" (ID 0x301) frame per Defender_DBC_v1.txt.
 * FuelUsed_L has no data source yet (would need a consumption integrator,
 * not just a level sender) so it is sent as the "not available" placeholder. */
CAN_MESSAGE_BUS packFuelStatusMSG(ANALOG_INPUT_BUS data){
    CAN_MESSAGE_BUS packedData;
    unsigned int  fuelAdcAvg;
    unsigned int  lvSupplyAdcAvg;
    float         fuelSupplyV;
    float         fuelOhms;
    float         fuelLiters;
    float         fuelPercent;
    unsigned int  fuelLevelRaw;
    unsigned int  fuelUsedRaw = FUEL_LEVEL_FAULT_RAW; /* not fitted - no consumption tracking yet */
    unsigned char fuelPctRaw;
    unsigned char fuelLowWarn;
    unsigned char fuelSenderRawByte;

    fuelAdcAvg     = averageAdcSamples(data.anInputExternal8, ADC_SAMPLE_COUNT);
    lvSupplyAdcAvg = averageAdcSamples(data.anLvSupply, ADC_SAMPLE_COUNT);
    fuelSupplyV    = lvSupplyVolts(lvSupplyAdcAvg);
    fuelOhms       = fuelSenderOhms(fuelAdcAvg, fuelSupplyV);
    fuelLiters     = fuelLevelLiters(fuelOhms);

    if (fuelLiters < 0.0f){
        /* open circuit fault */
        fuelLevelRaw = FUEL_LEVEL_FAULT_RAW;
        fuelPctRaw   = 0xFFU;
        fuelLowWarn  = 1U; /* fail safe - treat unknown level as a low-fuel warning */
    } else {
        fuelLevelRaw = (unsigned int)(fuelLiters * 10.0f + 0.5f); /* round to nearest 0.1L */
        fuelPercent  = (fuelLiters / FUEL_LEVEL_MAX_L) * 100.0f;
        fuelPctRaw   = (unsigned char)((fuelPercent / 0.5f) + 0.5f); /* 0.5%/bit per DBC scale */
        fuelLowWarn  = (fuelLiters < FUEL_LOW_WARN_L) ? 1U : 0U;
    }
    fuelSenderRawByte = (unsigned char)(fuelAdcAvg >> 4); /* coarse 12-bit -> 8-bit raw diagnostic value */

    packedData.ID = FUEL_STATUS_ID;
    packedData.Length = 0x08U;
    packedData.Extended = 0x00U;

    packedData.Data[0] = (unsigned char)(fuelLevelRaw & 0xFF);
    packedData.Data[1] = (unsigned char)((fuelLevelRaw >> 8) & 0xFF);
    packedData.Data[2] = (unsigned char)(fuelUsedRaw & 0xFF);
    packedData.Data[3] = (unsigned char)((fuelUsedRaw >> 8) & 0xFF);
    packedData.Data[4] = fuelPctRaw;
    packedData.Data[5] = fuelLowWarn;
    packedData.Data[6] = fuelSenderRawByte;
    packedData.Data[7] = 0U; /* Fuel_Reserved */

    return packedData;
}

/* Uptime_s_LSB is only 8 bits wide in the DBC (no companion MSB signal), so
 * it's a wrapping "still counting up" liveness indicator, not an absolute
 * clock - it rolls over every 256 seconds (~4.3 minutes). simulinkModelStepTime_uS
 * (declared in can_input_simulink.h) gives the actual model step period in
 * microseconds, so accumulating it here tracks real elapsed time regardless
 * of the configured step rate.
 * Note the "static unsigned int uptimeAccumUs" below: unlike the local
 * variables used elsewhere in this file, a variable declared "static"
 * INSIDE a function keeps its value between calls instead of being
 * reset every time the function runs - it's initialised to 0 once, then
 * simply carries on accumulating each time user_model_step() calls this. */
static unsigned char heartbeatUptimeLowByte(void){
    static unsigned int uptimeAccumUs = 0U;
    uptimeAccumUs += simulinkModelStepTime_uS;
    return (unsigned char)((uptimeAccumUs / 1000000U) & 0xFFU);
}

/* Rolling frame counter (0-255, wraps automatically) so other nodes can
 * confirm this message is actually being refreshed and not stuck/stale.
 * Same "static local" persistence trick as heartbeatUptimeLowByte above -
 * the wrap from 255 back to 0 happens for free, because unsigned char
 * arithmetic in C is defined to wrap (modulo 256) rather than overflow. */
static unsigned char heartbeatRollingCounter(void){
    static unsigned char counter = 0U;
    unsigned char current = counter;
    counter++;
    return current;
}

/* pack CAN1 "Node_Heartbeat" (ID 0x3F0) frame per Defender_DBC_v1.txt.
 * Broadcasts this xCU's identity/version, live LV supply rail voltage
 * (shared helper with the fuel sender correction), and a rolling counter. */
CAN_MESSAGE_BUS packNodeHeartbeatMSG(ANALOG_INPUT_BUS data, unsigned char faultCount, unsigned char lastFaultCode){
    CAN_MESSAGE_BUS packedData;
    unsigned int  lvSupplyAdcAvg;
    float         supplyV;
    unsigned int  supplyRaw;
    unsigned char supplyByte;

    lvSupplyAdcAvg = averageAdcSamples(data.anLvSupply, ADC_SAMPLE_COUNT);
    supplyV        = lvSupplyVolts(lvSupplyAdcAvg);
    supplyRaw      = (unsigned int)((supplyV * 10.0f) + 0.5f); /* 0.1V/bit per DBC scale */
    if (supplyRaw > 255U){
        supplyRaw = 255U; /* clamp to SupplyV_0p1V's 0-25.5V DBC range */
    }
    supplyByte = (unsigned char)supplyRaw;

    packedData.ID = NODE_HEARTBEAT_ID;
    packedData.Length = 0x08U;
    packedData.Extended = 0x00U;

    packedData.Data[0] = (unsigned char)HEARTBEAT_NODE_ID;
    packedData.Data[1] = (unsigned char)HEARTBEAT_SW_MAJOR;
    packedData.Data[2] = (unsigned char)HEARTBEAT_SW_MINOR;
    packedData.Data[3] = heartbeatUptimeLowByte();
    packedData.Data[4] = faultCount;
    packedData.Data[5] = lastFaultCode;
    packedData.Data[6] = supplyByte;
    packedData.Data[7] = heartbeatRollingCounter();

    return packedData;
}

/* --- Powertrain supervisor (Stage 3) ---------------------------------------
 * Receive and decode happens in powertrain.c, this section only gathers the
 * raw frames and switch states.
 *
 * CAN3 receive boxes
 *   box 1  LD controller 0x100 (11-bit)
 *   box 2..5  iNetic ISG_MCU_STATUS1..4 (29-bit)
 * CAN1 receive box
 *   box 1  drive mode request 0x302 from the display (11-bit):
 *          byte 0 = mode (0 Engine only, 1 EV, 2 Hybrid), byte 1 = rolling
 *          counter. ID and layout chosen by Red, not yet in the DBC.
 * "New frame" is detected by a change in the box timestamp, so it does not
 * depend on the timestamp unit. TO CONFIRM WITH MARC: that Timestamp only
 * changes on reception, and that a receive box accepts 29-bit IDs with the
 * mask used below. If either is wrong every frame times out, which is safe
 * (zero torque, drive not enabled).
 *
 * Digital inputs (PROPOSED, confirm against the loom)
 *   B11 DIN12 brake pedal switch, high = pressed (cal brake_active_high)
 * A missing, invalid or frozen mode request selects Engine only (zero
 * motor torque), see mode_source.c.
 */
#define LD_RX_BOX            1.0
#define ISG_RX_BOX_FIRST     2.0
#define MODE_RX_BOX          1.0
#define RX_MASK_STD          0x000007FFU
#define RX_MASK_EXT          0x1FFFFFFFU
#define ISG_RX_DLC           8U

static Powertrain    g_pt;
static unsigned char g_ptReady = 0U;
static double        g_rxTimestamp[2U + SF_COUNT] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

static void copyFrame(CAN_MESSAGE_BUS msg, double *lastTs, unsigned char *isNew,
                      unsigned char *len, unsigned char data[8]){
    unsigned char j;

    *isNew  = (msg.Timestamp != *lastTs) ? 1U : 0U;
    *lastTs = msg.Timestamp;
    *len    = msg.Length;
    for (j = 0U; j < 8U; j++){
        data[j] = msg.Data[j];
    }
}

static void gatherPowertrainInputs(PtInputs *in, DIGITAL_INPUT_BUS dig, ANALOG_INPUT_BUS ana){
    static const unsigned int isgId[SF_COUNT] = {
        (unsigned int)ID_ISG_MCU_STATUS1, (unsigned int)ID_ISG_MCU_STATUS2,
        (unsigned int)ID_ISG_MCU_STATUS3, (unsigned int)ID_ISG_MCU_STATUS4
    };
    CAN_MESSAGE_BUS msg;
    unsigned char   i;
    float           lvVolts;

    msg = dcan3MessageboxRead(LD_RX_BOX, (double)ID_LD_STATUS, RX_MASK_STD, g_cal.ld_rx_dlc);
    copyFrame(msg, &g_rxTimestamp[0], &in->ld_new, &in->ld_len, in->ld_data);

    for (i = 0U; i < SF_COUNT; i++){
        msg = dcan3MessageboxRead(ISG_RX_BOX_FIRST + (double)i, (double)isgId[i], RX_MASK_EXT, ISG_RX_DLC);
        copyFrame(msg, &g_rxTimestamp[1U + i], &in->s_new[i], &in->s_len[i], in->s_data[i]);
    }

    /* drive mode request, CAN1 */
    msg = dcan1MessageboxRead(MODE_RX_BOX, (double)ID_MODE_REQUEST, RX_MASK_STD, g_cal.mode_rx_dlc);
    copyFrame(msg, &g_rxTimestamp[1U + SF_COUNT], &in->mode_new, &in->mode_len, in->mode_data);

    in->din_brake = (dig.digitalInput12 != 0U) ? 1U : 0U;

    lvVolts = lvSupplyVolts(averageAdcSamples(ana.anLvSupply, ADC_SAMPLE_COUNT));
    if (lvVolts < 0.0f){
        lvVolts = 0.0f;
    }
    if (lvVolts > 6000.0f){
        lvVolts = 6000.0f;
    }
    in->lv_dv = (unsigned short)((lvVolts * 10.0f) + 0.5f);

    in->uds_inhibit = (rtB.inhibitDrive != 0.0) ? 1U : 0U;
}

/* Model entry point functions */

/* code required to initialise model here */
extern void user_model_initialize(void){
    /* every digital output off, CAN transceivers out of standby (see safety_gate.c).
     * The supervisor itself is initialised on the first step, once the step
     * period (simulinkModelStepTime_uS) is known. */
    gate_init_outputs();
}

/* this will be run at the specified time interval from the model step task  */
extern void user_model_step(void){
    //model step function variables
    DIGITAL_INPUT_BUS digitalInputs;
    ANALOG_INPUT_BUS analogInputs;
    CAN_MESSAGE_BUS engineTemps1Tx;
    CAN_MESSAGE_BUS fuelStatusTx;
    CAN_MESSAGE_BUS nodeHeartbeatTx;
    PtInputs ptIn;
    PtOutputs ptOut;

    //read inputs
    digitalInputs = digitalInputRead();
    analogInputs  = analogInputRead();

    //powertrain supervisor: decode, monitor, fault manager, state machine,
    //torque request. Final command and digital outputs come from the safety gate only.
    if (g_ptReady == 0U){
        pt_init(&g_pt, &g_cal, g_throttleMaps, (unsigned short)(simulinkModelStepTime_uS / 1000U));
        g_ptReady = 1U;
    }
    gatherPowertrainInputs(&ptIn, digitalInputs, analogInputs);
    pt_step(&g_pt, &ptIn, &ptOut);
    gate_commit(&ptOut.cmd, &g_cal);

    //Stage 1 sensor frames
    engineTemps1Tx  = packEngineTemps1MSG(analogInputs);
    fuelStatusTx    = packFuelStatusMSG(analogInputs);
    nodeHeartbeatTx = packNodeHeartbeatMSG(analogInputs, ptOut.fault_count, ptOut.last_fault);

    //CAN 2 is the UDS bootloader bus - no application traffic
    //CAN 1 = confirmed Stage 1 sensor-logging bus (Defender_VCU_xCU_Mapping_updated.xlsx).
    //Engine_Temps1 (0x110) - coolant temperature (ERR2081), buffer 1, 500ms interval
    dcan1Messagebox1Transmit(engineTemps1Tx, 1U, (double)500,(double)1);
    //Fuel_Status (0x301) - fuel level sender, buffer 2, 500ms interval
    dcan1Messagebox1Transmit(fuelStatusTx, 1U, (double)500,(double)2);
    //Node_Heartbeat (0x3F0) - identity/version/supply/liveness, buffer 3, 1000ms interval
    dcan1Messagebox1Transmit(nodeHeartbeatTx, 1U, (double)1000,(double)3);

}

/* if any steps are required on shutdown insert them here */
extern void user_model_terminate(void){

}
