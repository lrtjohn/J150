#include "sci_rx_isr.h"
#include "sci_service.h"

void PFAL_SCIB_RX_ISR(void)
{
   Sci_B_Receive(gScibRxQue);
}
