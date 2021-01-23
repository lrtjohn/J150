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

#define UPDATE_WATCHDOG_TIMER_COUNT		(gTimerCnt.watchDogCnt++)				

#define IS_WATCH_DOG_TIMER_EXPIRE       (gTimerCnt.watchDogCnt >= gTimerCnt.WatchDogCntThreshold)

#define RESET_WATCH_DOG_TIMER_CNT       (gTimerCnt.watchDogCnt = 0)

TIMER_INTERVAL_CNT gTimerCnt = 
{
    0,      // watch dog
    12,     // watch dog threshold
	0,
	0,
	0
};

int16 pwrBus_Vltge_Que_Init [PWRBUS_LEN] = {ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO,ZERO};

_PF_T0_RING_BUFFER pwrBus_Vltge_Que = {};

void Init_Timer0_Buf(void)
{
	pwrBus_Vltge_Que.newP = ZERO;
	pwrBus_Vltge_Que.oldP = ZERO;
	pwrBus_Vltge_Que.bufferLen = PWM_LEN;
	pwrBus_Vltge_Que.buffer = pwrBus_Vltge_Que_Init;
}

int PwrBusVotlageEnQueue(Uint16 newData, _PF_T0_RING_BUFFER *pbuf)
{
	static int isfull = 0;
	if(((pbuf -> oldP + ONE) % (pbuf -> bufferLen)) == (pbuf -> newP))
	{
		pbuf -> newP = (pbuf -> newP + ONE) % pbuf -> bufferLen;
		isfull = 1;
	}
	else
	{
		isfull = 0;
	}

	pbuf -> buffer[pbuf -> oldP] = newData;
	pbuf -> oldP = (pbuf -> oldP + ONE) % pbuf -> bufferLen;
	return isfull;
}

void PwrBusVoltageMonitor(void)
{
	static int cnt_UnderVoltage = 0;
	static int cnt_NormalVoltage = 0;
	static int cnt_VoltageDelta = 0;
	static int pwrbus_buildup = 0;
	static int pwrbus_delta = 0;
	static int cnt_UnderWarnLimit = 0;

	static int tmp_cnt = 0;

	if(gSysAnalogVar.single.var[updatePower270V_M].value > gSysAnalogVar.single.var[updatePower270V_M].min2nd){
		cnt_UnderVoltage = 0;
		cnt_UnderWarnLimit = 0;
		if(pwrbus_buildup == 0){
			++cnt_NormalVoltage;
			PwrBusVotlageEnQueue(gSysAnalogVar.single.var[updatePower270V_M].value, &pwrBus_Vltge_Que);
			if(cnt_NormalVoltage > PWRBUS_BUILTUP_TIMES){
				pwrbus_buildup = 1;
				tmp_cnt = 1;
				CLR_J150_POWER_BUS;
			}
		}
		else{
			if(PwrBusVotlageEnQueue(gSysAnalogVar.single.var[updatePower270V_M].value, &pwrBus_Vltge_Que)){
				pwrbus_delta = (pwrBus_Vltge_Que.buffer[pwrBus_Vltge_Que.oldP])-(pwrBus_Vltge_Que.buffer[pwrBus_Vltge_Que.newP]);
				if(pwrbus_delta > PWRBUS_VOLTAGE_DELTA){
					cnt_VoltageDelta = 0;
					CLR_J150_POWER_BUS;
				}
				else{
					if(cnt_VoltageDelta > PWRBUS_FULCHGR_TIMES){
						if(IS_SYS_BUS_CURRENT_ALARM){
							if(tmp_cnt == 1){
								tmp_cnt = 0;
								HARDWARE_OVER_CURRENT_CLEAR();
							}
						}
						SET_J150_POWER_BUS;
						CLEAR_SYS_BUS_UNDER_VOLTAGE_ALARM;
						CLEAR_BUS_UND_VOLT_PROT;
						CLEAR_BUS_UNDER_VOLT_WARN;
					}
					else ++cnt_VoltageDelta;
				}
			}
			else cnt_VoltageDelta = 0;
		}
	}
	else if(gSysAnalogVar.single.var[updatePower270V_M].value < gSysAnalogVar.single.var[updatePower270V_M].min){
		++cnt_UnderVoltage;
		++cnt_UnderWarnLimit;
		cnt_NormalVoltage = 0;
		cnt_VoltageDelta = 0;
		if(cnt_UnderVoltage > PWRBUS_UNDERVL_TIMES){
			pwrbus_buildup = 0;
			CLR_J150_POWER_BUS;
			Init_Timer0_Buf();
			SET_SYS_BUS_UNDER_VOLTAGE_ALARM;
			SET_BUS_UND_VOLT_PROT;
			SET_BUS_UNDER_VOLT_WARN;
		}
	}
	else{
		cnt_NormalVoltage = 0;
		cnt_VoltageDelta = 0;
		++cnt_UnderWarnLimit;
		if(cnt_UnderWarnLimit > PWRBUS_UNWARNL_TIMES){
			SET_BUS_UNDER_VOLT_WARN;
		}

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
	int16 tmp_TargetDuty;
	gSpwmPara.CurrentCompensateDuty = CurrentCompensate();
//	gSpwmPara.CurrentCompensateDuty = 0;
	gSpwmPara.OpenLoopDuty = OpenLoop_Process(&gOpenLoop_Para);
	gSpwmPara.CloseLoopDuty = Pid_Process(&gPID_Speed_Para);
//	gSpwmPara.CloseLoopDuty = 0;
	tmp_TargetDuty = gSpwmPara.CloseLoopDuty + gSpwmPara.OpenLoopDuty + gSpwmPara.CurrentCompensateDuty;
//	tmp_TargetDuty = gSpwmPara.CloseLoopDuty + gSpwmPara.OpenLoopDuty;
	if(tmp_TargetDuty > 1250) tmp_TargetDuty = 1250;
	else if(tmp_TargetDuty < 0) tmp_TargetDuty = 0;
	else; /*DO NOTHING*/
	gSpwmPara.TargetDuty = tmp_TargetDuty;
}

void PFAL_Timer0_ISR(void)
{
	GpioDataRegs.GPBDAT.bit.GPIO49 = 1; /*进程监视用*/
#if (SYS_DEBUG == INCLUDE_FEATURE)
    gtimertest++;
#endif

    UPDATE_WATCHDOG_TIMER_COUNT; /*5ms中断内部看门狗喂狗计数器累加*/

	PwrBusVoltageMonitor(); /*母线电压监控*/

	SYS_STATE_MACHINE; /*状态机管理*/

	MotorSpeed(); /*计算反馈转速并进行卡尔曼滤波*/

	/*DEBUG START*/
//        gSciAppProtocolTx_J150.currentSpeed = gEcapPara.gMotorSpeedEcap;
//        gSciAppProtocolTx_J150.currentSpeed = gSysAnalogVar.single.var[updatePower270V_M].value;
	/*DEBUG END*/

    if (IS_WATCH_DOG_TIMER_EXPIRE)
    {
        RESET_WATCH_DOG_TIMER_CNT;

        TOOGLE_CTL_BOARD_WATCHDOG;
    }

    if((gEcapPara.gMotorSpeedEcap < (4000)) && (gEcapPara.gMotorSpeedEcap > (1000))){
    	GpioDataRegs.GPCDAT.bit.GPIO68 = 0;
    }
    else if((gEcapPara.gMotorSpeedEcap > (4100)) || (gEcapPara.gMotorSpeedEcap > (900))){
    	GpioDataRegs.GPCDAT.bit.GPIO68 = 1;
    }

    GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1; /*进程监视用*/
}
