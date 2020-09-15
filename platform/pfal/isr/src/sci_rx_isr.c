#include "sci_rx_isr.h"
#include "sci_service.h"
void PFAL_SCIA_RX_ISR(void)
{

}

void PFAL_SCIB_RX_ISR(void)
{
   Sci_B_Receive(gScibRxQue);
}

void PFAL_SCIC_RX_ISR(void)
{
     
}

