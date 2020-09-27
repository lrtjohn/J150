#ifndef PF_TIMER0_ISR_H_
#define PF_TIMER0_ISR_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sci_j150.h"   // DSP2833x Examples Include File

typedef struct _TIMER_INTERVAL_CNT
{
    Uint16 watchDogCnt;
    Uint16 WatchDogCntThreshold;
    Uint16 controlCnt;
    Uint16 controlCntTreshold;
    Uint16 sciTxCnt;
    Uint16 sciTxCntTreshold;
}TIMER_INTERVAL_CNT;

void PFAL_Timer0_ISR(void);
#endif
