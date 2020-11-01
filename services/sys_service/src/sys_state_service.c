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
/*初始化状态*/
void Sys_hlstInit(void)
{
	gTimerCnt.Cnt_SM_Stop_5ms= 0;
	gTimerCnt.Cnt_SM_Alarm_5ms = 0;
	DISABLE_BUSBAR_VOLTAGE;
	DISABLE_GATE_DRIVER();
	if(gSpwmPara.Cnt_PWM_Init_BIT >= CNT_INIT_END){
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
					ENABLE_GATE_DRIVER();
					ENABLE_BUSBAR_VOLTAGE;
				}
				else{
					DISABLE_GATE_DRIVER();
					DISABLE_BUSBAR_VOLTAGE;
				} 
				/*如果开优化则需要放开等待语句，否则GPIO7的值更改后，不会立即生效
				*asm (" NOP");
				*/
				if(IS_BUSBAR_ENABLED){
					ENABLE_GATE_DRIVER();
					ENABLE_BUSBAR_VOLTAGE;
					if(gTimerCnt.Cnt_PwrBus < 5) ++gTimerCnt.Cnt_PwrBus;
					else Sys_chstForwardRotate();
				}
				else{
					DISABLE_GATE_DRIVER();
					DISABLE_BUSBAR_VOLTAGE;
					gTimerCnt.Cnt_PwrBus = 0;
				}
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
			Sys_chstAlarm();
		}
		else if(IS_SYS_ENABLE_STOP_ROTATE)
		{
			DISABLE_GATE_DRIVER();
			DISABLE_BUSBAR_VOLTAGE;
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
}

void Sys_hlsAlarm(void) /*故障保护状态*/
{
	DISABLE_GATE_DRIVER();
	DISABLE_BUSBAR_VOLTAGE;
	SET_SYS_ENABLE_STOP_ROTATE;
	gTimerCnt.Cnt_SM_Stop_5ms = 0;
	if(gTimerCnt.Cnt_SM_Alarm_5ms < 10) ++gTimerCnt.Cnt_SM_Alarm_5ms;
	if(gSysStateFlag.j150WorkMode == NORMAL){
		if(IS_SYS_ALARM){
			if(gTimerCnt.Cnt_SM_Alarm_5ms > 4) HARDWARE_OVER_CURRENT_CLEAR();
		}
		else{
			if(gTimerCnt.Cnt_SM_Alarm_5ms >= 8){
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
    }
    INIT_SYS_ROTATE_DIRECTION; /*电机驱动系统初始化为停止态*/
//    SET_J150_BIT_ING;
    gSysVersionNum = 0; /*版本号*/
}

void checkInputGPIOs (void){
	if(GpioDataRegs.GPADAT.bit.GPIO30 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO29 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO6 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO8 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO10 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO11 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPADAT.bit.GPIO14 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO32 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO33 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO52 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO53 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO58 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO61 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO66 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO69 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO70 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO71 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO72 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO73 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO74 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO75 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO76 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO79 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO38 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO34 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO36 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO46 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO47 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO80 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO81 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO82 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO83 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO85 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO86 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPCDAT.bit.GPIO87 == 0) SET_HW_DIGITAL_LEVEL_ALARM;
	else CLEAR_HW_DIGITAL_LEVEL_ALARM;
	if(GpioDataRegs.GPBDAT.bit.GPIO39 == 1) SET_HW_DIGITAL_LEVEL_ALARM;
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
