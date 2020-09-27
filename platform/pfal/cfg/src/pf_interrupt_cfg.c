#include "pf_interrupt_cfg.h"

const CFG_INTERRUPT_TBL CfgInterruptTbl_Default[] =
{
    TIMER0_ISR,
    TIMER1_ISR,
};
void CFG_INTERRUPT(CFG_ISR_ENABLE isrEnable)
{

    switch (isrEnable)
    {
    case TIMER0_ISR:
        /* code */
        PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
        break;
    case TIMER1_ISR:
        IER |= M_INT13;//timer1
        /* code */
        break;
    case EPWM1:
        /* code */
        PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
        break;
    case ECAP1:
        /* code */
        break;
    case ECAP4:
        /* code */
    	PieCtrlRegs.PIEIER4.bit.INTx4 = 1;//ECAP4
        break;
    case ECAP5:
        /* code */
    	PieCtrlRegs.PIEIER4.bit.INTx5 = 1;//ECAP5
        break;
    case ECAP6:
        /* code */
    	PieCtrlRegs.PIEIER4.bit.INTx6 = 1;//ECAP6
        break;
    case SCIARX:
        /* code */
        break;
    case SCIATX:
        /* code */
        break;
    case SCIBRX:
        /* code */
        PieCtrlRegs.PIEIER9.bit.INTx3 = 1;
        break;
    case SCIBTX:
        /* code */
        PieCtrlRegs.PIEIER9.bit.INTx4 = 1;
        break;
    case SCICRX:
        /* code */
        PieCtrlRegs.PIEIER8.bit.INTx5 = 1;
        break;
    case SCICTX:
        /* code */
        PieCtrlRegs.PIEIER8.bit.INTx6 = 1;
        break;
    default:
        break;
    }

}

const CFG_INTERRUPT_HDL_TBL SDB_CfgInterruptHdlTbl[TOTAL_INTERRUPT] =
{
    CFG_INTERRUPT
};


void PFAL_INTERRUPT_CFG(CFG_INTERRUPT_TBL* cfgInterruptTbl, int len)
{
#if(PF_ISR == INCLUDE_FEATURE)
    int i;
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    IER |= M_INT1;
    IER |= M_INT2;
    IER |= M_INT3;
    IER |= M_INT4;
    IER |= M_INT7;
    IER |= M_INT8;//SCIc
    IER |= M_INT9;//SCIa//ECAN//scib

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEACK.all = 0xFFFF;

    for(i = 0; i < len; ++i)
	{
	    SDB_CfgInterruptHdlTbl[0](cfgInterruptTbl[i].cfgIsrEnable);
	}

    EINT;   // Enable Global interrupt INTM
    ERTM;
    ScicRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    ScicRegs.SCIFFTX.bit.TXFFINTCLR = 1;
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
#endif
}

