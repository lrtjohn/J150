#include "sys_state_service.h"


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
void Sys_hlstBackwardRotate(void);
void Sys_hlsWarning(void);
void Sys_hlsAlarm(void);

#define Sys_chstInit()                  Sys_hlstPtr = Sys_hlstInit; SET_SYS_RUNNING_STATE_INIT;
#define Sys_chstStop()                  Sys_hlstPtr = Sys_hlsStop; SET_SYS_RUNNING_STATE_STOP;
#define Sys_chstForwardRotate()         Sys_hlstPtr = Sys_hlstForwardRotate; SET_SYS_RUNNING_STATE_FORWARD_RUN;
#define Sys_chstBackwardRotate()        Sys_hlstPtr = Sys_hlstBackwardRotate; SET_SYS_RUNNING_STATE_BACKWARD_RUN;
#define Sys_chstWarning()               Sys_hlstPtr = Sys_hlsWarning; SET_SYS_RUNNING_STATE_WARNING;
#define Sys_chstAlarm()                 Sys_hlstPtr = Sys_hlsAlarm; SET_SYS_RUNNING_STATE_ALARM;


#define SYS_STATE_MACHINE_INIT        Sys_chstInit()  
void Sys_hlstInit(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

//    if(IS_SYS_WARNING)
//    {
//        Sys_chstWarning();
//        return;
//    }

    Sys_chstStop();
}

void Sys_hlsStop(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

//    if(IS_SYS_WARNING)
//    {
//        Sys_chstWarning();
//        return;
//    }

    if(IS_SYS_ENABLE_FORWARD_ROTATE)
    {
        Sys_chstForwardRotate();
        return;
    }

//    if(IS_SYS_ENABLE_BACKWARD_ROTATE)
//    {
//        Sys_chstBackwardRotate();
//        return;
//    }
}

void Sys_hlstForwardRotate(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

//    if(IS_SYS_WARNING)
//    {
//        Sys_chstWarning();
//        return;
//    }

    if(IS_SYS_ENABLE_STOP_ROTATE)
    {
    	Sys_chstStop();
    	return;
    }
}

void Sys_hlstBackwardRotate(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

    if(IS_SYS_WARNING)
    {
        Sys_chstWarning();
        return;
    }
}



void Sys_hlsWarning(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

    if(IS_SYS_WARNING)
    {
        Sys_chstWarning();
        return;
    }

    Sys_chstStop();
}

void Sys_hlsAlarm(void)
{
    if(IS_SYS_ALARM)
    {
        Sys_chstAlarm();
        return;
    }

//    if(IS_SYS_WARNING)
//    {
//        Sys_chstWarning();
//        return;
//    }

    Sys_chstStop();
}

void Init_Sys_State_Service(void)
{
    CLEAR_SYS_ALARM;
    CLEAR_SYS_WARNING;
    CLEAR_SYS_ERROR;
    INIT_SYS_RUNNING_STATE;            
    INIT_SYS_ROTATE_DIRECTION;
    SYS_STATE_MACHINE_INIT;
//    SET_J150_BIT_ING;
    gSysVersionNum = 0;
}
