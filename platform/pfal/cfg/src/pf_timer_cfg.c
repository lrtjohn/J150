#include "pf_timer_cfg.h"




const CFG_TIMER_TBL CFG_TIMER_INFO[] =
{

    {
        TIMER0,       //sci moudule, A, B, C
        200,         //sci rx gpio index
        120          //sci tx gpio index
    },
    {
        TIMER1, 
        200,
        120
    }
};

void CFG_TIMER0(CFG_TIMER_TBL cfgTimerTblElement)
{
	ConfigCpuTimer(&CpuTimer0, cfgTimerTblElement.sysFrequency, cfgTimerTblElement.period);//t = freq * priod/150000000,0.2ms
    CpuTimer0Regs.TCR.bit.TIE= 1;
    CpuTimer0Regs.TCR.bit.TSS = 0;
}

void CFG_TIMER1(CFG_TIMER_TBL cfgTimerTblElement)
{
    ConfigCpuTimer(&CpuTimer1, cfgTimerTblElement.sysFrequency, cfgTimerTblElement.period);
    CpuTimer1Regs.TCR.bit.TIE= 1;
    CpuTimer1Regs.TCR.bit.TSS = 0;
}

const CFG_TIMER_HDL_TBL SDB_CfgTimerHdlTbl[TOTAL_TIMER] =
{
     CFG_TIMER0,
     CFG_TIMER1
};

void PFAL_TIMER_CFG(CFG_TIMER_TBL* cfgTimerTbl, int len)
{
#if(PF_TIMER == INCLUDE_FEATURE)
    int i;
    InitCpuTimers();
    EALLOW;

    for(i = 0; i < len; ++i)
    {
        SDB_CfgTimerHdlTbl[cfgTimerTbl[i].timerEnable](cfgTimerTbl[i]);
    }
    EDIS;
#endif
}

































