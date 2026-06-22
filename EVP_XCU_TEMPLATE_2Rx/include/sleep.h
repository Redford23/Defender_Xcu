/*
 * sleep.h
 *
 *  Created on: 14 Feb 2025
 *      Author: mOffice
 */

#ifndef INCLUDE_SLEEP_H_
#define INCLUDE_SLEEP_H_

/*
 * user defined functions for XCU hardware sleep
 */

void prvStartTickInterruptTimer(void);
void prvStopTickInterruptTimer(void);
void prvSleep(void);
void vSetWakeTimeInterrupt(unsigned int ExpectedIdleTime );
unsigned long ulGetExternalTime(void);


#endif /* INCLUDE_SLEEP_H_ */
