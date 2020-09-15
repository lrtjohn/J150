#include "sci_tx_isr.h"


void PFAL_SCIA_TX_ISR(void)
{

}

void PFAL_SCIB_TX_ISR(void)
{

    SCI_B_Transmit(gScibTxQue);
}

void PFAL_SCIC_TX_ISR(void)
{
    
}
