#ifndef PF_TIMER_CFG_H_
#define PF_TIMER_CFG_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

#define TOTAL_TIMER 2

typedef enum
{
    TIMER0,
    TIMER1,
}TIMER_ENABLE;

typedef struct
{
    TIMER_ENABLE timerEnable;
    Uint16 period;
    Uint16 sysFrequency;
}CFG_TIMER_TBL;

typedef void (*CFG_TIMER_HDL_TBL)(CFG_TIMER_TBL cfgSciTblElement);

void PFAL_TIMER_CFG(CFG_TIMER_TBL* cfgTimerTbl, int len);
#endif
