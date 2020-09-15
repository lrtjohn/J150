#include "pwm_isr.h"
#include "prod.h"

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gpwmisr = 0;
#endif
void PFAL_PWM_ISR(void)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gpwmisr++;
#endif
    Spwm_Output(&gSpwmPara);
}

