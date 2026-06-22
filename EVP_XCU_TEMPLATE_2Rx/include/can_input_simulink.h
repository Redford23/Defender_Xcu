/*
 * can_input_simulink.h
 *
 *  Created on: 1 Feb 2022
 *      Author: MarcWork
 */

#ifndef INCLUDE_CAN_INPUT_SIMULINK_H_
#define INCLUDE_CAN_INPUT_SIMULINK_H_

#define TX_MESSAGE_BOX_COUNT  32
#define XCP_TX_MESSAGE_BOX_COUNT 1
#define XCP_RX_MESSAGE_BOX_COUNT 1
#define XCP_CAN_TX_MESSAGE_BOX 32
#define RX_MESSAGE_BOX_COUNT  32
#define CHECKTIMESTAMP
#define ADC_SAMPLE_COUNT 12
#define DOUT_STATUS_SAMPLE_COUNT 4

#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_

typedef struct {
    unsigned char Extended;
    unsigned char Length;
    unsigned char Remote;
    unsigned char Error;
    unsigned int ID;
    double Timestamp;
    unsigned char Data[8];
} CAN_MESSAGE_BUS;

#endif

typedef struct {
    unsigned char digitalInput0;
    unsigned char digitalInput1;
    unsigned char digitalInput2;
    unsigned char digitalInput3;
    unsigned char digitalInput4;
    unsigned char digitalInput5;
    unsigned char digitalInput6;
    unsigned char digitalInput12;
    unsigned char pGood1;
    unsigned char pGood2;
} DIGITAL_INPUT_BUS;

typedef struct {
    unsigned char digitalOutput1;
    unsigned char digitalOutput2;
    unsigned char digitalOutput3;
    unsigned char digitalOutput4;
    unsigned char digitalOutput5;
    unsigned char digitalOutput6;
    unsigned char digitalOutput7;
    unsigned char digitalOutput8;
    unsigned char digitalOutput9;
    unsigned char digitalOutput10;
    unsigned char digitalOutput11;
    unsigned char digitalOutput12;
    unsigned char vPuEnable;
    unsigned char canStandby1;
    unsigned char canStandby2;
    unsigned char canStandby3;
} DIGITAL_OUTPUT_BUS;

typedef struct {
        unsigned int doutStatus1;
        unsigned int doutStatus2;
        unsigned int doutStatus3;
        unsigned int doutStatus4;
        unsigned int doutStatus5;
        unsigned int doutStatus6;
        unsigned int doutStatus7;
        unsigned int doutStatus8;
        unsigned int doutStatus9;
        unsigned int doutStatus10;
        unsigned int doutStatus11;
        unsigned int doutStatus12;
} DIGITAL_OUPUT_STATUS_BUS;

typedef struct{
    unsigned int anInputExternal1[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal2[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal3[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal4[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal5[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal6[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal7[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal8[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal9[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal10[ADC_SAMPLE_COUNT];
    unsigned int anInputExternal11[ADC_SAMPLE_COUNT];
    unsigned int anLvSupply[ADC_SAMPLE_COUNT];

}ANALOG_INPUT_BUS;

typedef struct{
    unsigned reserved1:16;
    unsigned powerOnReset:1;
    unsigned OscillatorFail: 1;
    unsigned watchdogReset: 1;
    unsigned pllSlip: 1;
    unsigned reserved2: 7;
    unsigned cpuReset: 1;
    unsigned softwareReset: 1;
    unsigned externalReset: 1;
    unsigned reserved3: 3;
}RESET_BITS;

typedef union
{
    RESET_BITS bits;
    unsigned int data;
}RESET_CAUSES;

typedef struct{
    unsigned int highWaterMark;
    unsigned int runTimeCounter;
}MODEL_TASK_INFO;

typedef enum
{
    POWER_ON_RESET,
    OSCFAIL,
    WATCHDOGRESET,
    PLLSLIP,
    CPURESET,
    SOFTRESET,
    EXTERNALRESET
}RESETCAUSEFORSIMULINK;


unsigned char digitalOutput[16];
unsigned int pwmHoldDuty[2];   /**< Duty cycle in % of the period for hold in */
unsigned int period;     /**< Period in us                   */
float contactorCoilResNom;
float contactorHoldCurrentNom;
unsigned int pullInCountMax; /* pull in time /simulink task step time (e.g 20mS) */
unsigned char digitalInput[10];
unsigned char digital_output_status[12];

unsigned int anInput[12][ADC_SAMPLE_COUNT];

unsigned char dcanrx_data[3][RX_MESSAGE_BOX_COUNT][9];  //[1][0...7] is data, [i][8] is DLC
unsigned int dcan1rx_Id_timestamp[RX_MESSAGE_BOX_COUNT][2];  // [i][0] is for received id, [i][1] is timestamp
unsigned char dcan1tx_data[TX_MESSAGE_BOX_COUNT][8];
unsigned int dcan2rx_Id_timestamp[RX_MESSAGE_BOX_COUNT][2];  // [i][0] is for received id, [i][1] is timestamp
unsigned char dcan2tx_data[TX_MESSAGE_BOX_COUNT][8];
unsigned int dcan3rx_Id_timestamp[RX_MESSAGE_BOX_COUNT][2];  // [i][0] is for received id, [i][1] is timestamp
unsigned char dcan3tx_data[TX_MESSAGE_BOX_COUNT][8];
unsigned char dcan1Messagebox1Extended[TX_MESSAGE_BOX_COUNT];
unsigned char dcan2Messagebox1Extended[TX_MESSAGE_BOX_COUNT];
unsigned char dcan3Messagebox1Extended[TX_MESSAGE_BOX_COUNT];
unsigned char dcan1Messagebox1length[TX_MESSAGE_BOX_COUNT];
unsigned char dcan2Messagebox1length[TX_MESSAGE_BOX_COUNT];
unsigned char dcan3Messagebox1length[TX_MESSAGE_BOX_COUNT];
unsigned int dcan1TxEnable, dcan2TxEnable, dcan3TxEnable;
unsigned int dcan1Messagebox1Interval[TX_MESSAGE_BOX_COUNT][2];
unsigned int dcan2Messagebox1Interval[TX_MESSAGE_BOX_COUNT][2];
unsigned int dcan3Messagebox1Interval[TX_MESSAGE_BOX_COUNT][2];
unsigned int dcan1Messagebox1Id[TX_MESSAGE_BOX_COUNT];
unsigned int dcan2Messagebox1Id[TX_MESSAGE_BOX_COUNT];
unsigned int dcan3Messagebox1Id[TX_MESSAGE_BOX_COUNT];

unsigned int dcan1mask[RX_MESSAGE_BOX_COUNT];
unsigned int dcan2mask[RX_MESSAGE_BOX_COUNT];
unsigned int dcan3mask[RX_MESSAGE_BOX_COUNT];
unsigned int dcan1Filter[RX_MESSAGE_BOX_COUNT];
unsigned int dcan2Filter[RX_MESSAGE_BOX_COUNT];
unsigned int dcan3Filter[RX_MESSAGE_BOX_COUNT];
unsigned char dcan1RxDlc[RX_MESSAGE_BOX_COUNT];
unsigned char dcan2RxDlc[RX_MESSAGE_BOX_COUNT];
unsigned char dcan3RxDlc[RX_MESSAGE_BOX_COUNT];
unsigned int dcan1RxEnables, dcan2RxEnables, dcan3RxEnables;
unsigned int dcan1TxRqstSuccess, dcan2TxRqstSuccess, dcan3TxRqstSuccess;

volatile RESET_BITS resetCauseForSimulink;
unsigned int simulinkModelStepTime_uS;
unsigned int sysResetRequest;
unsigned int ulModelStackHighWaterMark;  /* The minimum amount of stack space that has remained for the task since the task was created.  The closer this value is to zero the closer the task has come to overflowing its stack. */
unsigned int ulModelStackRunTimeCounter; /* The total run time allocated to the task so far, as defined by the run time stats clock.  See https://www.FreeRTOS.org/rtos-run-time-stats.html.*/

/*can1*/
CAN_MESSAGE_BUS dcan1MessageboxRead (double messageBox, double canFilterID, unsigned int rxMask, unsigned char dlc );
void dcan1Messagebox1Transmit (CAN_MESSAGE_BUS txDataBus,  unsigned char enable, double txInterval, double buffer);

/*can2*/
CAN_MESSAGE_BUS dcan2MessageboxRead (double messageBox, double canFilterID, unsigned int rxMask, unsigned char dlc );
void dcan2Messagebox1Transmit (CAN_MESSAGE_BUS txDataBus,  unsigned char enable, double txInterval, double buffer);

/*can3*/
CAN_MESSAGE_BUS dcan3MessageboxRead (double messageBox, double canFilterID, unsigned int rxMask, unsigned char dlc );
void dcan3Messagebox1Transmit (CAN_MESSAGE_BUS txDataBus,  unsigned char enable, double txInterval, double buffer);

/* xcp */
unsigned char xcpMessageboxTransmit (CAN_MESSAGE_BUS txDataBus);
/* can status */
void dcanTxStatusGet (unsigned int txStatus[3]);

/* digital IO*/
DIGITAL_INPUT_BUS digitalInputRead (void);
void digitalOutputSet (DIGITAL_OUTPUT_BUS outputRequest, unsigned int Period_uS,
                       unsigned char holdDutyMin, unsigned int pullInTime_mS,
                       unsigned int coilResistanceNominalOhm, unsigned int holdCurrentNominalMa);
/* digital output status*/
DIGITAL_OUPUT_STATUS_BUS outputStatusMonitor(void);

/*analog inputs*/
ANALOG_INPUT_BUS analogInputRead(void);

/* reset causes */
RESETCAUSEFORSIMULINK resetCauseGet(void);

/* SL model task execution time including input and output functions*/
unsigned int modelStepExecutionTimeGet(void);

/* sets reset request to value for simulink task to generate reset */
void requestSystemReset(void);

/* gets info for model step task from freertos */
MODEL_TASK_INFO modelStepTaskInfoGet(void);

#endif /* INCLUDE_CAN_INPUT_SIMULINK_H_ */
