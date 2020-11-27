#include "sci_tx_isr.h"


void PFAL_SCIA_TX_ISR(void)
{

}

void PFAL_SCIB_TX_ISR(void)
{
	GpioDataRegs.GPBDAT.bit.GPIO60 = 1;

    SCI_B_Transmit(gScibTxQue);

    GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
}

void PFAL_SCIC_TX_ISR(void)
{
    
}
