#include "pf_pwm_cfg.h"


const CFG_PWM_TBL CfgPwmTbl[] =
{
    {
        PWM1A,          //pwm module selected
        40000           //pwm frequency
    },
    {
        PWM1B,
        40000
    },
    {
        PWM2A,
        40000
    },
    {
        PWM2B,
        40000
    },
    {
        PWM3A,
        40000
    },
    {
        PWM3B,
        40000
    },
    {
        PWM4A,
        40000
    },
    {
        PWM4B,
        40000
    },
    {
        PWM5A,
        40000
    },
    {
        PWM5B,
        40000
    },
    {
        PWM6A,
        40000
    },
    {
        PWM6B,
        40000
    }
};

void CFG_PWM_1A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    EDIS;
    EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
    EPwm1Regs.TBPRD = epwmPeriod;
	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm1Regs.TBCTR = 0x0000;
	EPwm1Regs.CMPA.half.CMPA = epwmPeriod/2;
	//EPwm1Regs.CMPB = EPWM2_TIMER_HALF_TBPRD;
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm1Regs.ETSEL.bit.INTEN = 1;
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;

	EPwm1Regs.ETSEL.bit.SOCAEN = 1;
	EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD;
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;

//	EPwm1Regs.DBCTL.all = 0x000b;
	EPwm1Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm1Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm1Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm1Regs.DBRED = 60;//180==1.5us
	EPwm1Regs.DBFED = 60;//180==1.5us
}
void CFG_PWM_1B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
    EDIS;

}
void CFG_PWM_2A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    EDIS;
	EPwm2Regs.TBPRD = epwmPeriod;
	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm2Regs.TBCTR = 0x0000;
	EPwm2Regs.CMPA.half.CMPA =epwmPeriod/2;
	//EPwm2Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm2Regs.ETSEL.bit.INTEN = 1;
	EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;


//	EPwm2Regs.DBCTL.all = 0xb;
	EPwm2Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm2Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm2Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm2Regs.DBRED = 60;
	EPwm2Regs.DBFED = 60;
}
void CFG_PWM_2B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO3 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
    EDIS;
}
void CFG_PWM_3A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    EDIS;
    EPwm3Regs.TBPRD = epwmPeriod;
	EPwm3Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm3Regs.TBCTR = 0x0000;
	EPwm3Regs.CMPA.half.CMPA =epwmPeriod/2;
	//EPwm3Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm3Regs.ETSEL.bit.INTEN = 1;
	EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;


//	EPwm3Regs.DBCTL.all = 0xb;
	EPwm3Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm3Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm3Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm3Regs.DBRED = 60;
	EPwm3Regs.DBFED = 60;
}
void CFG_PWM_3B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
    EDIS;
}
void CFG_PWM_4A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    EDIS;
    EPwm4Regs.TBPRD = epwmPeriod;
	EPwm4Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm4Regs.TBCTR = 0x0000;
	EPwm4Regs.CMPA.half.CMPA = epwmPeriod/2;
	//EPwm3Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm4Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm4Regs.ETSEL.bit.INTEN = 1;
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;


//	EPwm3Regs.DBCTL.all = 0xb;
	EPwm4Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm4Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm4Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm4Regs.DBRED = 60;
	EPwm4Regs.DBFED = 60;
}
void CFG_PWM_4B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
    EDIS;
}
void CFG_PWM_5A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;    // Enable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    EDIS;
    EPwm5Regs.TBPRD = epwmPeriod;
	EPwm5Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm5Regs.TBCTR = 0x0000;
	EPwm5Regs.CMPA.half.CMPA = epwmPeriod/2;
	//EPwm3Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm5Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm5Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm5Regs.ETSEL.bit.INTEN = 1;
	EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;


//	EPwm3Regs.DBCTL.all = 0xb;
	EPwm5Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm5Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm5Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm5Regs.DBRED = 60;
	EPwm5Regs.DBFED = 60;
}
void CFG_PWM_5B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up on GPIO9 (EPWM5B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
    EDIS;
}
void CFG_PWM_6A(CFG_PWM_TBL cfgPwmTblElement)
{
	Uint16 epwmPeriod;
	epwmPeriod = (Uint16)(120000/cfgPwmTblElement.cfgPwmParam.Frequency/2);
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;    // Enable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;   // Configure GPIO10 as EPWM6A
    EDIS;
    EPwm6Regs.TBPRD = epwmPeriod;
	EPwm6Regs.TBPHS.half.TBPHS = 0x0000;
	EPwm6Regs.TBCTR = 0x0000;
	EPwm6Regs.CMPA.half.CMPA = epwmPeriod/2;
	//EPwm3Regs.CMPB = EPWM1_TIMER_HALF_TBPRD;
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm6Regs.AQCTLB.bit.CAU = AQ_CLEAR;
	EPwm6Regs.AQCTLB.bit.CAD = AQ_SET;
	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;
	EPwm6Regs.ETSEL.bit.INTEN = 1;
	EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;


//	EPwm3Regs.DBCTL.all = 0xb;
	EPwm6Regs.DBCTL.bit.IN_MODE = 2;//EPWMxA rising edge delay , EPWMXB falling edge delay
	EPwm6Regs.DBCTL.bit.POLSEL = 2;  //EPWMxB  invert
	EPwm6Regs.DBCTL.bit.OUT_MODE = 3;
	EPwm6Regs.DBRED = 60;
	EPwm6Regs.DBFED = 60;
}
void CFG_PWM_6B(CFG_PWM_TBL cfgPwmTblElement)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up on GPIO11 (EPWM6B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;   // Configure GPIO11 as EPWM6B
    EDIS;
}


const CFG_PWM_HDL_TBL SDB_CfgPwmHdlTbl[TOTAL_PWM] =
{
     CFG_PWM_1A,
     CFG_PWM_1B,
     CFG_PWM_2A,
     CFG_PWM_2B,
     CFG_PWM_3A,
     CFG_PWM_3B,
     CFG_PWM_4A,
     CFG_PWM_4B,
     CFG_PWM_5A,
     CFG_PWM_5B,
     CFG_PWM_6A,
     CFG_PWM_6B
};


void PFAL_PWM_CFG(CFG_PWM_TBL* cfgPwmTbl, int len)
{
#if(PF_PWM == INCLUDE_FEATURE)
    int i = 0;
    EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
    for(i = 0; i < len; ++i)
    {
        SDB_CfgPwmHdlTbl[cfgPwmTbl[i].cfgPwmModule.pwmModule](cfgPwmTbl[i]);
    }
    EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;
#endif
}

