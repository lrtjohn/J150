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
#include "ecap_service.h"
#include "pid_service.h"

#define PWM_DUTY_BASE 1250 /*30KHz为1250，50KHz为750*/
#define K_MAXDUTY 		  (0.2786)
#define B_MAXDUTY 		  (103.14)

typedef enum _PWM_RUNNING_STATE
{
    PWM_INIT,
    PWM_FORWARD_RUN,
    PWM_STOP,
    PWM_ALARM
}PWM_RUNNING_STATE;

typedef struct _SPWM_PARA
{
//    int16 Phase_Duty_U;
//    int16 Phase_Duty_V;
//    int16 Phase_Duty_W;
    int16 Duty;
    int16 Duty_Gradual_mid;
//    int16 Rvdt_Pos;
//    Uint16 Rvdt_Current_Pos;
//    int16 Rvdt_Zero;
    int16 DutyAddInterval;
    int16 DutyAddIntervalCnt;
    int16 Duty_Gradual;
    int16 TargetDuty;
    int16 StepMaxDuty;
    double BusVolt_Ratio;
    int16 lastDuty;
    int16 ThresholdDutyP;
    int16 ThresholdDutyN;
    int16 OpenLoopDuty;
    int16 CloseLoopDuty;
    int16 CurrentCompensateDuty;
    Uint16 CurrentHallPosition;
    Uint16 LastHalllPosition;
    SYS_RUNNING_STATE pwmSM;
    Uint16 restrictduty;
    Uint16 Cnt_PWM_Init_BIT;
}SPWM_PARA;

typedef PF_RING_BUFFER PWM_CURRENT_QUE;
extern PWM_CURRENT_QUE* pwm_busCurrent_Que;
void Init_PWM_Buf(void);
int PwmBusCurrentEnQueue(Uint16 e, PWM_CURRENT_QUE *PWMBusCurrentQue);
Uint16 GetCurrentHallValue(void);
void Spwm_Output(SPWM_PARA* spwmPara);
void Init_Spwm_Service(void);
void Spwm_HighSpeed_BIT(SPWM_PARA* spwmPara);
void Pwm_Init_BIT(SPWM_PARA* spwmPara);
void Duty_Gradual_Change (SPWM_PARA* spwmPara);
void OverCurrentSoftProtect(SPWM_PARA* spwmPara);
extern SPWM_PARA gSpwmPara;
#endif
