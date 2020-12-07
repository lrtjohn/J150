#ifndef PID_SERVICE_H_
#define PID_SERVICE_H_

typedef struct _PID_VAR
{
    double targetVal;
    double currentVal;
    double currentErr;
    double sumErr;
    double currentErrThreshold;
    double sumErrThreshold;
    double outputPosThresh;
    double outputNegThresh;
    double kp0;
    double ki0;
    double ka;
    double kb;
}PID_VAR;

typedef struct _OPENLOOP_VAR
{
    double currentBusVoltage;
    double nominalBusVoltage;
    double volt_Ratio;
    double targetSpeed;
    double openloop_K;
    double openloop_B;
}OPENLOOP_VAR;

double Pid_Process(PID_VAR* pidVar);
double OpenLoop_Process(OPENLOOP_VAR* openloopVar);
double CurrentCompensate(void);
void Init_PID_Service(void);
void Init_OpenLoop_Service(void);
extern PID_VAR gPID_Speed_Para;
extern OPENLOOP_VAR gOpenLoop_Para;

#endif
