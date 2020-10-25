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
    20       // sci tx threshold
};

PWRBUS_VLTGE_QUE* pwrBus_Vltge_Que = NULL;

void Init_Timer0_Buf(void)
{
	if(pwrBus_Vltge_Que == NULL)
	{
		pwrBus_Vltge_Que = (PWRBUS_VLTGE_QUE*)malloc(sizeof(PWRBUS_VLTGE_QUE));
		if(pwrBus_Vltge_Que == NULL)
		{
			//TODO generate alarm
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		pwrBus_Vltge_Que->front = 0;
		pwrBus_Vltge_Que->rear = 0;
		pwrBus_Vltge_Que->bufferLen = 10;
		pwrBus_Vltge_Que->buffer = (Uint16*)malloc(sizeof(Uint16) * pwrBus_Vltge_Que->bufferLen);
		if(pwrBus_Vltge_Que->buffer == NULL)
		{
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		memset(pwrBus_Vltge_Que->buffer, 0 , sizeof(pwrBus_Vltge_Que->buffer));
	}
}

int PwrBusVotlageEnQueue(Uint16 e, PWRBUS_VLTGE_QUE *PWRBUSVoltageQue)
{
	static int isfull = 0;
	if((PWRBUSVoltageQue->rear + 1) % (PWRBUSVoltageQue->bufferLen) == PWRBUSVoltageQue->front)
	{
		PWRBUSVoltageQue->front = (PWRBUSVoltageQue->front + 1) % (PWRBUSVoltageQue->bufferLen);
		isfull = 1;
	}
	else{
		isfull = 0;
	}

	PWRBUSVoltageQue->buffer[PWRBUSVoltageQue->rear] = e;
	PWRBUSVoltageQue->rear = (PWRBUSVoltageQue->rear + 1) % (PWRBUSVoltageQue->bufferLen);
	return isfull;
}

void PwrBusVotlageClrQueue(PWRBUS_VLTGE_QUE *PWRBUSVoltageQue)
{
	PWRBUSVoltageQue->rear = 0;
	PWRBUSVoltageQue->front = 0;
}

void PwrBusVoltageMonitor(void)
{
	static int cnt_UnderVoltage = 0;
	static int cnt_NormalVoltage = 0;
	static int cnt_VoltageDelta = 0;
	static int pwrbus_buildup = 0;
	static int pwrbus_delta = 0;

	if(gSysAnalogVar.single.var[updatePower270V_M].value > gSysAnalogVar.single.var[updatePower270V_M].min2nd){
		cnt_UnderVoltage = 0;
		if(pwrbus_buildup == 0){
			++cnt_NormalVoltage;
			PwrBusVotlageEnQueue(gSysAnalogVar.single.var[updatePower270V_M].value, pwrBus_Vltge_Que);
			if(cnt_NormalVoltage > PWRBUS_BUILTUP_TIMES){
				pwrbus_buildup = 1;
				CLR_J150_POWER_BUS;
			}
		}
		else{
			if(!IS_J150_POWER_NOR){
				if(PwrBusVotlageEnQueue(gSysAnalogVar.single.var[updatePower270V_M].value, pwrBus_Vltge_Que)){
					pwrbus_delta = (pwrBus_Vltge_Que->buffer[pwrBus_Vltge_Que->rear])-(pwrBus_Vltge_Que->buffer[pwrBus_Vltge_Que->front]);
					if(pwrbus_delta < 0) pwrbus_delta = -pwrbus_delta;
					if(pwrbus_delta > PWRBUS_VOLTAGE_DELTA) cnt_VoltageDelta = 0;
					else{
						if(cnt_VoltageDelta > PWRBUS_FULCHGR_TIMES){
							SET_J150_POWER_BUS;
							CLEAR_SYS_BUS_UNDER_VOLTAGE_ALARM;
						}
						else ++cnt_VoltageDelta;
					}
				}
				else cnt_VoltageDelta = 0;
			}
		}
	}
	else if(gSysAnalogVar.single.var[updatePower270V_M].value < gSysAnalogVar.single.var[updatePower270V_M].min){
		++cnt_UnderVoltage;
		cnt_NormalVoltage = 0;
		cnt_VoltageDelta = 0;
		if(cnt_UnderVoltage > PWRBUS_UNDERVL_TIMES){
			pwrbus_buildup = 0;
			CLR_J150_POWER_BUS;
			PwrBusVotlageClrQueue(pwrBus_Vltge_Que);
			SET_SYS_BUS_UNDER_VOLTAGE_ALARM;
		}
	}
	else{
		cnt_NormalVoltage = 0;
		cnt_VoltageDelta = 0;
	}
}

void MotorSpeed(void){
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

void updateCtrlStrategyParameters(void)
{
	gPID_Speed_Para.currentVal = gEcapPara.gMotorSpeedEcap;
	gOpenLoop_Para.currentBusVoltage = gSysAnalogVar.single.var[updatePower270V_M].value;
}

void CtrlStrategyCalculation(void)
{
	gSpwmPara.CloseLoopDuty = Pid_Process(&gPID_Speed_Para);
	gSpwmPara.OpenLoopDuty = OpenLoop_Process(&gOpenLoop_Para);
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

        PwrBusVoltageMonitor();
        if(IS_SYS_ENABLE_FORWARD_ROTATE && IS_J150_POWER_NOR){
        	ENABLE_BUSBAR_VOLTAGE;

        }
        else{
        	DISABLE_BUSBAR_VOLTAGE;
        }
        gSciAppProtocolTx_J150.RFU = GpioDataRegs.GPADAT.bit.GPIO7;
        SYS_STATE_MACHINE;
        MotorSpeed();
//        gSciAppProtocolTx_J150.currentSpeed = gEcapPara.gMotorSpeedEcap;
        updateCtrlStrategyParameters();
        CtrlStrategyCalculation();

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
