#include "sys_state_service.h"
#include "pwm_hal.h"
#include "gpio_service.h"
#include "adc_service.h"
#include "ecap_service.h"
#include "spwm_service.h"
#include "timer0_isr.h"

SYS_STATE_FLAG gSysStateFlag = 
{
    STOP,
    0,
    0
};

Uint16 gSysVersionNum = 0;

void (*Sys_hlstPtr)(void);

void Sys_hlstInit(void);
void Sys_hlsStop(void);
void Sys_hlstForwardRotate(void);
void Sys_hlsAlarm(void);

#define Sys_chstInit()                  Sys_hlstPtr = Sys_hlstInit; SET_SYS_RUNNING_STATE_INIT;
#define Sys_chstStop()                  Sys_hlstPtr = Sys_hlsStop; SET_SYS_RUNNING_STATE_STOP;
#define Sys_chstForwardRotate()         Sys_hlstPtr = Sys_hlstForwardRotate; SET_SYS_RUNNING_STATE_FORWARD_RUN;
#define Sys_chstAlarm()                 Sys_hlstPtr = Sys_hlsAlarm; SET_SYS_RUNNING_STATE_ALARM;

#define SYS_STATE_MACHINE_INIT        Sys_chstInit()  

void KeyParametersClear(void){
	gSpwmPara.CloseLoopDuty = 0;
	gSpwmPara.OpenLoopDuty = 0;
	gSpwmPara.Duty_Gradual = 0;
	gSpwmPara.Duty = 0;
	gSpwmPara.TargetDuty = 0;
	gSpwmPara.StepMaxDuty = 0;
}

/*初始化状态*/
void Sys_hlstInit(void)
{
	gTimerCnt.Cnt_SM_Stop_5ms= 0;
	gTimerCnt.Cnt_SM_Alarm_5ms = 0;
	DISABLE_BUSBAR_VOLTAGE;
	DISABLE_GATE_DRIVER();
	CLR_J150_MOTOR_STA;
	if(gSpwmPara.Cnt_PWM_Init_BIT >= CNT_INIT_END){
		SET_J150_BIT_CMPLT;
		if(gSysStateFlag.j150WorkMode == NORMAL){
			if(IS_SYS_ALARM) {
				Sys_chstAlarm();
			}
			else {
				Sys_chstStop();
			}
		}
		else{
			/*战时模式*/
		}
	}
}

/*停止状态*/
void Sys_hlsStop(void)
{
	gTimerCnt.Cnt_SM_Alarm_5ms = 0;
	if(gTimerCnt.Cnt_SM_Stop_5ms < 4) gTimerCnt.Cnt_PwrBus = 0;
	if(gTimerCnt.Cnt_SM_Stop_5ms < 10) ++gTimerCnt.Cnt_SM_Stop_5ms;
	CLR_J150_MOTOR_STA;
	KeyParametersClear();
	if(gSysStateFlag.j150WorkMode == NORMAL){
		if(IS_SYS_ALARM){
			DISABLE_GATE_DRIVER();
			DISABLE_BUSBAR_VOLTAGE;						
			Sys_chstAlarm();
		}
		else{
			if(IS_SYS_ENABLE_FORWARD_ROTATE)
			{
				if(IS_J150_POWER_NOR && (gTimerCnt.Cnt_SM_Stop_5ms >=4)){
//					ENABLE_GATE_DRIVER();
					ENABLE_BUSBAR_VOLTAGE;
//					asm (" NOP");
//					asm (" NOP");
//					asm (" NOP");
					if(IS_BUSBAR_ENABLED){
						ENABLE_GATE_DRIVER();
//						ENABLE_BUSBAR_VOLTAGE;
						if(gTimerCnt.Cnt_PwrBus < 5) ++gTimerCnt.Cnt_PwrBus;
						else{
							Sys_chstForwardRotate();
						}
					}
					else{
						DISABLE_GATE_DRIVER();
//						DISABLE_BUSBAR_VOLTAGE;
						gTimerCnt.Cnt_PwrBus = 0;
					}
				}
				else{
					DISABLE_GATE_DRIVER();
					DISABLE_BUSBAR_VOLTAGE;
				} 
				//如果开优化则需要放开等待语句，否则GPIO7的值更改后，不会立即生效
//				asm (" NOP");
//				asm (" NOP");
//				asm (" NOP");
			}
			else{
					DISABLE_GATE_DRIVER();
					DISABLE_BUSBAR_VOLTAGE;
					gTimerCnt.Cnt_PwrBus = 0;				
			}
		}
	}
	else{
		/*战时模式*/
	}

}

void Sys_hlstForwardRotate(void) /*运行状态*/
{
	gTimerCnt.Cnt_SM_Stop_5ms = 0;
	gTimerCnt.Cnt_SM_Alarm_5ms = 0;
	if(gSysStateFlag.j150WorkMode == NORMAL){
		if(IS_SYS_ALARM)
		{
			DISABLE_GATE_DRIVER();
			DISABLE_BUSBAR_VOLTAGE;
			KeyParametersClear();
			Sys_chstAlarm();
		}
		else if(IS_SYS_ENABLE_STOP_ROTATE)
		{
			DISABLE_GATE_DRIVER();
			DISABLE_BUSBAR_VOLTAGE;
			KeyParametersClear();
			Sys_chstStop();
		}
		else{
				ENABLE_GATE_DRIVER();
				ENABLE_BUSBAR_VOLTAGE;
		}
	}
	else{
		/*战时模式*/
	}
	SET_J150_MOTOR_STA;
	updateCtrlStrategyParameters(); /*开闭环用反馈转速，反馈电压更新*/
	CtrlStrategyCalculation(); /*计算开环，闭环占空比，并赋值目标占空比*/
}

void Sys_hlsAlarm(void) /*故障保护状态*/
{
//	static int cnt_clear = 0;
	DISABLE_GATE_DRIVER();
	DISABLE_BUSBAR_VOLTAGE;
	SET_SYS_ENABLE_STOP_ROTATE;
	SET_J150_FAULT_EXT;
	CLR_J150_MOTOR_STA;
	KeyParametersClear();
	gTimerCnt.Cnt_SM_Stop_5ms = 0;
	if(gTimerCnt.Cnt_SM_Alarm_5ms < 10) ++gTimerCnt.Cnt_SM_Alarm_5ms;
	if(gSysStateFlag.j150WorkMode == NORMAL){
		if(IS_SYS_ALARM){
			if((gTimerCnt.Cnt_SM_Alarm_5ms > 4) && (gDebugDataArray[3] == 555)){
				HARDWARE_OVER_CURRENT_CLEAR();
			}
		}
		else{
			if(gTimerCnt.Cnt_SM_Alarm_5ms >= 8){
				CLR_J150_FAULT_EXT;
				Sys_chstStop(); 
			}			
		}
	}
	else{
		/*战时模式*/
		/*HARDWARE_OVER_CURRENT_CLEAR();*/
	}
}

void Init_Sys_State_Service(void)
{
    CLEAR_SYS_ALARM; /*清除故障告警*/
    CLEAR_SYS_WARNING;/*清除预警信号*/
    CLEAR_SYS_ERROR; /*清除错误信号*/
    {/*设置状态机*/
    INIT_SYS_RUNNING_STATE; /*状态机变量设置为为初始化*/
    SYS_STATE_MACHINE_INIT; /*状态机指针设置为初始化*/
    INIT_SYS_WORK_MODE;
    CLR_J150_BIT_CMPLT;
    CLR_J150_MOTOR_STA;
    INIT_SYS_STATUS;
    }
    INIT_SYS_ROTATE_DIRECTION; /*电机驱动系统初始化为停止态*/
//    SET_J150_BIT_ING;
    gSysVersionNum = 2; /*版本号*/
}

int test111 = 0;
void checkInputGPIOs (void){
	if(GpioDataRegs.GPADAT.bit.GPIO30 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 1;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
//	if(GpioDataRegs.GPADAT.bit.GPIO29 == 0){
//		SET_HW_DIGITAL_LEVEL_ALARM;
//		test111 = 2;
//	}
//	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO6 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 3;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO8 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 4;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO10 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 5;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO11 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 6;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO14 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 7;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO32 == 0){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 8;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO33 == 0){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 9;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO52 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 10;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO53 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 11;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO58 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 12;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO61 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 13;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO66 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 14;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO69 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 15;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO70 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 16;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO71 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 17;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO72 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 18;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO73 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 19;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO74 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 20;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO75 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 21;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO76 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 22;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO79 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 23;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO38 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 24;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO34 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 25;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO36 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 26;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO46 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 27;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO47 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 28;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO80 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 29;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO81 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 30;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO82 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 31;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO83 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 32;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO85 == 0){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 33;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO86 == 0){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 34;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO87 == 0){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 35;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO39 == 1){
		SET_HW_DIGITAL_LEVEL_ALARM;
		test111 = 36;
	}
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;


}

void checkOutputGPIOs (void){
	if(GpioDataRegs.GPADAT.bit.GPIO0 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO1 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO2 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO3 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO4 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO5 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO7 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO9 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO12 == 0) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO15 == 0) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO16 == 1) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO22 == 0) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO51 == 0) SET_SYS_HARDWARE_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO77 == 0) SET_SYS_HARDWARE_ALARM;
//	if(GpioDataRegs.GPCDAT.bit.GPIO78 == 1) SET_SYS_HARDWARE_ALARM;
}

void powerOn_BIT(void){ /*main函数进程*/
	checkOutputGPIOs();
	checkInputGPIOs();
}

void period_BIT(void){ /*main函数进程*/
	checkInputGPIOs(); /*固定电平数字量BIT*/
	DIGIT_SIG_ROUTING_INSPECTION(); /*各电压PG含硬件过流*/
	CheckMotorTemperature();
	CheckDriverTemperature();
	check_28V_Current();
	check_28V_Voltage();
	check_Analog_Ref();
	checkMotorSpeed();
}
