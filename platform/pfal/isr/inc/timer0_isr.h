#ifndef PF_TIMER0_ISR_H_
#define PF_TIMER0_ISR_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "sci_j150.h"

typedef struct _TIMER_INTERVAL_CNT
{
    Uint16 watchDogCnt;
    Uint16 WatchDogCntThreshold;
    Uint16 Cnt_SM_Stop_5ms;
    Uint16 Cnt_SM_Alarm_5ms;
    Uint16 Cnt_PwrBus;
}TIMER_INTERVAL_CNT;

#define PWRBUS_BUILTUP_TIMES (20)
#define PWRBUS_FULCHGR_TIMES (10)
#define PWRBUS_UNDERVL_TIMES (5)
#define PWRBUS_VOLTAGE_DELTA (10)

typedef PF_RING_BUFFER PWRBUS_VLTGE_QUE;
extern PWRBUS_VLTGE_QUE* pwrBus_Vltge_Que;

void Init_Timer0_Buf(void);
int PwrBusVotlageEnQueue(Uint16 e, PWRBUS_VLTGE_QUE *PWRBUSVoltageQue);
void PwrBusVotlageClrQueue(PWRBUS_VLTGE_QUE *PWRBUSVoltageQue);
void MotorSpeed(void);
void updateCtrlStrategyParameters(void);
void CtrlStrategyCalculation(void);
void PFAL_Timer0_ISR(void);
extern TIMER_INTERVAL_CNT gTimerCnt;
#endif
