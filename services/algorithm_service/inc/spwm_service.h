#ifndef SPWM_SERVICE_H_
#define SPWM_SERVICE_H_

// #include "DSP2833x_Gpio.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"
#include "sin_table.h"
#include "rvdt_service.h"
#include "pwm_hal.h"
#include "adc_service.h"
#include "sci_j150.h"
#include "gpio_service.h"

#define PWM_DUTY_BASE 750

typedef enum _PWM_RUNNING_STATE
{
    PWM_INIT,
    PWM_FORWARD_RUN,
    PWM_STOP,
    PWM_ALARM
}PWM_RUNNING_STATE;

typedef struct _SPWM_PARA
{
    int16 Phase_Duty_U;
    int16 Phase_Duty_V;
    int16 Phase_Duty_W;
    int16 Duty;
    int16 Duty_Gradual;
    int16 Rvdt_Pos;
    Uint16 Rvdt_Current_Pos;
    int16 Rvdt_Zero;
    int16 DutyAddInterval;
    int16 DutyAddIntervalCnt;
    int16 TargetDuty;
    int16 Ddtmax;
    int16 ThresholdDutyP;
    int16 ThresholdDutyN;
    int16 OpenLoopDuty;
    int16 CloseLoopDuty;
    Uint16 CurrentHallPosition;
    Uint16 LastHalllPosition;
    PWM_RUNNING_STATE pwmSM;
}SPWM_PARA;

Uint16 GetCurrentHallValue(void);
void Spwm_Output(SPWM_PARA* spwmPara);
void Init_Spwm_Service(void);
extern SPWM_PARA gSpwmPara;
#endif
