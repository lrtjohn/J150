#include "pid_service.h"

PID_VAR gPID_Speed_Para = {0};
OPENLOOP_VAR gOpenLoop_Para = {0};

double OpenLoop_Process(OPENLOOP_VAR* openloopVar){
	double openloop_Output = 0;

	openloop_Output = (openloopVar->targetSpeed * openloopVar->openloop_K + openloopVar->openloop_B) * (openloopVar->nominalBusVoltage / openloopVar->currentBusVoltage);

	return openloop_Output;
}

double Pid_Process(PID_VAR* pidVar)
{
    double pidOutput = 0;

    pidVar->currentErr = (pidVar->targetVal - (pidVar->currentVal));
    if((pidVar->currentErr > -pidVar->currentErrThreshold) && (pidVar->currentErr < pidVar->currentErrThreshold))
    {
        if((( pidVar->currentErr > 0) && (pidVar->sumErr < pidVar->sumErrThreshold)) || ((pidVar->currentErr < 0) && (pidVar->sumErr > -pidVar->sumErrThreshold)))
        {
            pidVar->sumErr = pidVar->sumErr + pidVar->currentErr;
        }
    }
    else
    {
         pidVar->sumErr = 0;
    }
    
    pidOutput = (int)(pidVar->currentErr * pidVar->kp) + (int)(pidVar->sumErr * pidVar->ki);

    if(pidOutput > pidVar->outputThreshold)
    {
        pidOutput = pidVar->outputThreshold;
    }
    else if(pidOutput < -pidVar->outputThreshold)
    {
        pidOutput = -pidVar->outputThreshold;
    }

    return pidOutput;
}

void Init_PID_Service(void)
{
	gPID_Speed_Para.targetVal = 1700;
	gPID_Speed_Para.currentVal = 0;
	gPID_Speed_Para.currentErr = 0;
	gPID_Speed_Para.sumErr = 0;
	gPID_Speed_Para.currentErrThreshold = 500;
	gPID_Speed_Para.sumErrThreshold = 1171070;
	gPID_Speed_Para.outputThreshold = 700;
	gPID_Speed_Para.kp = 300;
	gPID_Speed_Para.ki = 400;
}

void Init_OpenLoop_Service(void)
{
	gOpenLoop_Para.currentBusVoltage = 0;
	gOpenLoop_Para.nominalBusVoltage = 1729;
	gOpenLoop_Para.targetSpeed = 0;
	gOpenLoop_Para.openloop_K = 0.7286;
	gOpenLoop_Para.openloop_B = -4396.3;
}
