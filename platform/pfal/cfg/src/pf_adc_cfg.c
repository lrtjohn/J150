#include "pf_adc_cfg.h"

#define TOTAL_ADC 1

void CFG_ADC(CFG_ADC_TBL cfgAdcTblElement)
{
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x0005;

	AdcRegs.ADCTRL1.bit.ACQ_PS = 0x0002;

	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1; //0:Sequential Sampling Mode; 1:Simultaneous Sampling Mode
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; //0:Dual Sequencer; 1:Cascaded Sequencer

	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;

	AdcRegs.ADCMAXCONV.all = 0x0007; //set 8 conversions, using SEQ1

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; //ADCINA0/B0
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1; //ADCINA1/B1
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2; //ADCINA2/B2
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3; //ADCINA3/B3
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4; //ADCINA4/B4
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5; //ADCINA5/B5
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6; //ADCINA6/B6
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7; //ADCINA7/B7

	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;



//    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0; //ADCINA0
//    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1; //ADCINA1
//    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2; //ADCINA2
//    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3; //ADCINA3
//    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4; //ADCINA4
//    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5; //ADCINA5
//    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6; //ADCINA6
//    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7; //ADCINA7
//    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8; //ADCINB0
//    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9; //ADCINB1
//    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xa; //ADCINB2
//    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xb; //ADCINB3
//    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xc; //ADCINB4
//    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xd; //ADCINB5
//    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xe; //ADCINB6
//    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xf; //ADCINB7

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; //Set PWMA SOC trigger
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
//    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
//    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
}

const CFG_ADC_HDL_TBL SDB_CfgAdcHdlTbl[TOTAL_ADC] =
{
    CFG_ADC
};

void PFAL_ADC_CFG(CFG_ADC_TBL* cfgAdcTbl, int len)
{
#if(PF_ADC == INCLUDE_FEATURE)
    int i = 0; 
    InitAdc();
    for(i = 0; i < len; ++i)
    {
	    SDB_CfgAdcHdlTbl[0](cfgAdcTbl[i]);
    }
#endif
}

