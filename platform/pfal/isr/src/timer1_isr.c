#include "timer1_isr.h"
#include "prod.h"


#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimer1test = 0;
#endif

void PFAL_Timer1_ISR(void)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif
}
