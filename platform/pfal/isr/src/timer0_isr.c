#include "timer0_isr.h"
#include "prod.h"
#include "gpio_service.h"
#include "sci_protocal.h"
#include "ecap_service.h"
#include "kalman_service.h"
#include "spwm_service.h"
#include "pid_service.h"
#include "adc_service.h"
#include <string.h>

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimertest = 0;
#endif

/* Interval unit: ms */
#define TIME_BASE_INTERVAL  (5)
#define TIME_SCI_TX_INTERVAL            (20 / TIME_BASE_INTERVAL)
#define TIME_FEED_WATCH_DOG_INTERVAL    (60 / TIME_BASE_INTERVAL)

#define UPDATE_TIMER_COUNT(){                                       \
                                gTimerCnt.controlCnt++;             \
                                gTimerCnt.sciTxCnt++;               \
                                gTimerCnt.watchDogCnt++;            \
                            }

#define IS_WATCH_DOG_TIMER_EXPIRE       (gTimerCnt.watchDogCnt >= gTimerCnt.WatchDogCntThreshold)
#define IS_SCI_TX_TIMER_EXPIRE          (gTimerCnt.sciTxCnt >= gTimerCnt.sciTxCntTreshold)
#define IS_CONTROL_TIMER_TIMER_EXPIRE   (gTimerCnt.controlCnt >= gTimerCnt.controlCntTreshold)

#define RESET_WATCH_DOG_TIMER_CNT       (gTimerCnt.watchDogCnt = 0)
#define RESET_SCI_TX_TIMER_CNT          (gTimerCnt.sciTxCnt  = 0)
#define RESET_CONTROL_TIMER_TIMER_CNT   (gTimerCnt.controlCnt = 0)

TIMER_INTERVAL_CNT gTimerCnt = 
{
    0,      // watch dog
    12,     // watch dog threshold
    0,      // control 
    1,      // control threshold
    0,      // sci tx 
    4       // sci tx threshold
};

void MotorSpeed(){
	static int count = 0;
//	int calSpeed = -1;

  	if (gEcapPara.isEcapRefresh == 1){

  		gKF_Speed.currentData = CalculateSpeed(gEcapPara.gECapCount);
		if(gKF_Speed.currentData != -1){
			gEcapPara.gMotorSpeedEcap = KalmanVarFilter(&gKF_Speed);
		}
		gEcapPara.isEcapRefresh = 0;
		count = 0;
  	}
  	else{
		count++;
		if(count > 5){
			gKF_Speed.currentData = 0;
			gEcapPara.gMotorSpeedEcap = KalmanVarFilter(&gKF_Speed);
			count = 0;
		}
  	}
}

void PFAL_Timer0_ISR(void)
{
#if (SYS_DEBUG == INCLUDE_FEATURE)
    gtimertest++;
#endif

    UPDATE_TIMER_COUNT();

    if (IS_CONTROL_TIMER_TIMER_EXPIRE)
    {
        RESET_CONTROL_TIMER_TIMER_CNT;
        MotorSpeed();
        gPID_Speed_Para.currentVal = gEcapPara.gMotorSpeedEcap;
        gPID_Speed_Para.targetVal = gSciAppProtocolRx_J150.targetSpeed;
        gOpenLoop_Para.currentBusVoltage = gSysAnalogVar.single.var[updatePower270V_M].value;
        gOpenLoop_Para.currentSpeed = gEcapPara.gMotorSpeedEcap;

        gSpwmPara.CloseLoopDuty = Pid_Process(&gPID_Speed_Para);
        gSpwmPara.OpenLoopDuty = OpenLoop_Process(&gOpenLoop_Para);
    }

    if (IS_WATCH_DOG_TIMER_EXPIRE)
    {
        RESET_WATCH_DOG_TIMER_CNT;

        TOOGLE_CTL_BOARD_WATCHDOG;
//	    TOOGLE_DRIVE_BOARD_WATCHDOG;
    }

    if (IS_SCI_TX_TIMER_EXPIRE)
    {
        RESET_SCI_TX_TIMER_CNT;

        SCI_TX_PackData(gScibTxQue);
    }
}
