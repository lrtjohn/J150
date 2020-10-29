#include "sys_state_service.h"
#include "pwm_hal.h"
#include "gpio_service.h"


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
	DISABLE_BUSBAR_VOLTAGE;
	DISABLE_SW_BREAK;
	DISABLE_GATE_DRIVER();
	Disable_All_Epwms();
    if(IS_SYS_ALARM) {
    	Sys_chstAlarm();
    }
    else {
    	Sys_chstStop();
    }
}

/*停止状态*/
void Sys_hlsStop(void)
{
	DISABLE_BUSBAR_VOLTAGE;
	DISABLE_SW_BREAK;
	DISABLE_GATE_DRIVER();
	Disable_All_Epwms();
    if(IS_SYS_ALARM) {
    	Sys_chstAlarm();
    }
    else{
        if(IS_SYS_ENABLE_FORWARD_ROTATE)
        {
            if(IS_J150_POWER_NOR){
            	ENABLE_BUSBAR_VOLTAGE;
            	/*考虑延迟确保可控硅关断*/
            	Sys_chstForwardRotate();
            }
            else{
            	DISABLE_BUSBAR_VOLTAGE;
            }
        }
    }
}

void Sys_hlstForwardRotate(void) /*运行状态*/
{
    if(IS_SYS_ALARM)
    {
    	DISABLE_GATE_DRIVER();
    	DISABLE_SW_BREAK;
    	Disable_All_Epwms();
        Sys_chstAlarm();
    }
    else if(IS_SYS_ENABLE_STOP_ROTATE)
    {
    	DISABLE_GATE_DRIVER();
    	DISABLE_SW_BREAK;
    	Disable_All_Epwms();
    	Sys_chstStop();
    }
}

void Sys_hlsAlarm(void) /*故障保护状态*/
{
	DISABLE_BUSBAR_VOLTAGE;
	DISABLE_SW_BREAK;
	DISABLE_GATE_DRIVER();
	Disable_All_Epwms();
    if(IS_SYS_ALARM) { Sys_chstAlarm(); }
    else { Sys_chstStop(); }
}

void Init_Sys_State_Service(void)
{
    CLEAR_SYS_ALARM; /*清除故障告警*/
    CLEAR_SYS_WARNING;/*清除预警信号*/
    CLEAR_SYS_ERROR; /*清除错误信号*/
    {/*设置状态机*/
    INIT_SYS_RUNNING_STATE; /*状态机变量设置为为初始化*/
    SYS_STATE_MACHINE_INIT; /*状态机指针设置为初始化*/
    }
    INIT_SYS_ROTATE_DIRECTION; /*电机驱动系统初始化为停止态*/
//    SET_J150_BIT_ING;
    gSysVersionNum = 0; /*版本号*/
}
