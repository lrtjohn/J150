#ifndef PID_SERVICE_H_
#define PID_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File

typedef struct _PID_VAR
{
    double targetVal;
    double currentVal;
    double currentErr;
    double sumErr;
    double currentErrThreshold;
    double sumErrThreshold;
    double outputThreshold;
    double kp;
    double ki;
}PID_VAR;

typedef struct _OPENLOOP_VAR
{
    Uint16 currentBusVoltage;
    Uint16 nominalBusVoltage;
    double currentSpeed;
    double openloop_K;
    double openloop_B;
}OPENLOOP_VAR;

double Pid_Process(PID_VAR* pidVar);
double OpenLoop_Process(OPENLOOP_VAR* openloopVar);
void Init_PID_Service(void);
void Init_OpenLoop_Service(void);
extern PID_VAR gPID_Speed_Para;
extern OPENLOOP_VAR gOpenLoop_Para;

#endif
