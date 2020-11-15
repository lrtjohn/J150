#include "pid_service.h"
#include "spwm_service.h"
PID_VAR gPID_Speed_Para = {0};
OPENLOOP_VAR gOpenLoop_Para = {0};

double OpenLoop_Process(OPENLOOP_VAR* openloopVar){
	double openloop_Output = 0;

	openloop_Output = (openloopVar->targetSpeed * openloopVar->openloop_K + openloopVar->openloop_B) * openloopVar->volt_Ratio;
/*增加限幅*/
	return openloop_Output;
}

double Pid_Process(PID_VAR* pidVar)
{
    double pidOutput = 0;

    pidVar->currentErr = (pidVar->targetVal - (pidVar->currentVal));
    if((pidVar->currentErr > -(pidVar->currentErrThreshold)) && (pidVar->currentErr < pidVar->currentErrThreshold))
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
	gPID_Speed_Para.targetVal = 500;
	gPID_Speed_Para.currentVal = 0;
	gPID_Speed_Para.currentErr = 0;
	gPID_Speed_Para.sumErr = 0;
	gPID_Speed_Para.currentErrThreshold = 600;
	gPID_Speed_Para.sumErrThreshold = 4200000;
	gPID_Speed_Para.outputThreshold = 1100;
	gPID_Speed_Para.kp = 0.3;
	gPID_Speed_Para.ki = 0.000168;
}

void Init_OpenLoop_Service(void)
{
	gOpenLoop_Para.currentBusVoltage = 0;
	gOpenLoop_Para.nominalBusVoltage = 2585;
	gOpenLoop_Para.volt_Ratio = 0.794;
	gOpenLoop_Para.targetSpeed = 0;
	gOpenLoop_Para.openloop_K = 0.2292;
	gOpenLoop_Para.openloop_B = -123.83;
}
