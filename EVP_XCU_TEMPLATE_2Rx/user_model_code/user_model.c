/*
 * user_model.c
 *
 *  Created on: 17 Jun 2026
 *      Author: mOffice
 */

#include "user_model.h"

/* user model constants */
#define TEST_MESSAGE1_ID 0x123
#define TEST_MESSAGE2_ID 0x124
#define TEST_MESSAGE3_ID 0x125


/* user model functions */
CAN_MESSAGE_BUS packDigitalInputsMSG(DIGITAL_INPUT_BUS data){
    CAN_MESSAGE_BUS packedData;
    packedData.ID = TEST_MESSAGE1_ID;
    packedData.Length = 0x08U;
    packedData.Extended = 0x00U;
    packedData.Data[0] = data.digitalInput0;
    packedData.Data[1] = data.digitalInput1;
    packedData.Data[2] = data.digitalInput2;
    packedData.Data[3] = data.digitalInput3;
    packedData.Data[4] = data.digitalInput4;
    packedData.Data[5] = data.digitalInput5;
    packedData.Data[6] = data.digitalInput6;
    packedData.Data[7] = data.digitalInput12;

    return packedData;
}

CAN_MESSAGE_BUS packAnInputsMSG (ANALOG_INPUT_BUS data){
    CAN_MESSAGE_BUS packedData;
    packedData.ID = TEST_MESSAGE2_ID;
    packedData.Length = 0x08U;
    packedData.Extended = 0x00U;
    packedData.Data[0] = data.anLvSupply[0]; // pack first sample of supply voltage for demo


    return packedData;
}

/* Model entry point functions */

/* code required to initialise model here */
extern void user_model_initialize(void){
    DIGITAL_OUTPUT_BUS digitalOutputsInit;
 // clear global data
 //set any states and parameters to required values
  //e.g: userModelState = INITIALISED;
    //set outputs
    digitalOutputsInit.canStandby1 = 1;
    digitalOutputsInit.canStandby2 = 0;
    digitalOutputsInit.canStandby3 = 1;

    digitalOutputSet (digitalOutputsInit,1000U,100U,100U,40U,156U); // constants to turn pwm function off

}

/* this will be run at the specified time interval from the model step task  */
extern void user_model_step(void){
    //model step function variables
    DIGITAL_INPUT_BUS  digitalInputs;
    DIGITAL_OUTPUT_BUS digitalOutputs;
    ANALOG_INPUT_BUS analogInputs;
    CAN_MESSAGE_BUS exampleCanRx;
    CAN_MESSAGE_BUS exampleCanTx;
    CAN_MESSAGE_BUS exampleCanTx2;


    //read inputs
    digitalInputs = digitalInputRead ();
    analogInputs =  analogInputRead();
    //receive can data
    exampleCanRx = dcan2MessageboxRead ((double) 1, (double)TEST_MESSAGE3_ID , 0x000007ff, 0x08);


    //call model functions
/* @Red the control functions go here */
    digitalOutputs.digitalOutput1 = exampleCanRx.Data[0];

    exampleCanTx = packDigitalInputsMSG(digitalInputs);
    exampleCanTx2 = packAnInputsMSG(analogInputs);

/* end of user funstions */

    //set outputs - ensure state of can standby
    digitalOutputs.canStandby1 = 1;
    digitalOutputs.canStandby2 = 0;
    digitalOutputs.canStandby3 = 1;
    digitalOutputSet (digitalOutputs,1000U,100U,100U,40U,156U); // constants to turn pwm function off

    //transmit can data @Red add messages here as required
    //CAN 2 message box 1 is assigned to UDS bootloader
    dcan2Messagebox1Transmit(exampleCanTx, 1U, (double)100,(double)2);
    dcan2Messagebox1Transmit(exampleCanTx2, 1U, (double)100,(double)3);

}

/* if any steps are required on shutdown insert them here */
extern void user_model_terminate(void){

}
