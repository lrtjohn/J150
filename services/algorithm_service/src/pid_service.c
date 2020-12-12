#include "pid_service.h"
#include "spwm_service.h"
#include "kalman_service.h"
PID_VAR gPID_Speed_Para = {0};
OPENLOOP_VAR gOpenLoop_Para = {0};

#define COMPENSATE_DUTY_K	(0.36) //0.36 LUG DEBUG

double OpenLoop_Process(OPENLOOP_VAR* openloopVar){
	double openloop_Output = 0;

	openloop_Output = (openloopVar->targetSpeed * openloopVar->openloop_K + openloopVar->openloop_B) * openloopVar->volt_Ratio;
/*增加限幅*/
	if(openloop_Output > 1250) openloop_Output = 1250;
	else if(openloop_Output < 0) openloop_Output = 0;
	else /*DO NOTHING*/;

	return openloop_Output;
}

double CurrentCompensate(void){
	double Compensate_Duty = 0;
	int16 I_busCurrent = 0;

    gKF_Current.currentData = gCurrent_Struct.I_bus_RBUF_Sum >> 7;
    gCurrent_Struct.I_busCurrent_Ave = KalmanVarFilter(&gKF_Current);

	I_busCurrent = gCurrent_Struct.I_busCurrent_Ave;
	if(I_busCurrent < 62) I_busCurrent = 0;
	else if(I_busCurrent > 1000) I_busCurrent = 1000;
	else; /*DO NOTHING*/
	Compensate_Duty = I_busCurrent * COMPENSATE_DUTY_K * 0.805;
	if(Compensate_Duty > 400) Compensate_Duty = 400;
	else if(Compensate_Duty < 0) Compensate_Duty = 0;
	else;/*DO NOTHING*/
	return Compensate_Duty;
}

double Pid_Process(PID_VAR* pidVar)
{
    double pidOutput = 0;
    double kp = 0;
    double ki = 0;

    kp = pidVar->kp0 * (1 + pidVar->ka * (1 + (gCurrent_Struct.I_busCurrent_Ave / 25)));
    ki = pidVar->ki0 * (1 + pidVar->kb * (1 + (gCurrent_Struct.I_busCurrent_Ave / 25)));

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
    
    pidOutput = (int)(pidVar->currentErr * kp) + (int)(pidVar->sumErr * ki);

    if(pidOutput > pidVar->outputPosThresh)
    {
        pidOutput = pidVar->outputPosThresh;
    }
    else if(pidOutput < pidVar->outputNegThresh)
    {
        pidOutput = pidVar->outputNegThresh;
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
	gPID_Speed_Para.sumErrThreshold = 807692;    //1050000;   // 2100000;
	gPID_Speed_Para.outputPosThresh = 1100;
	gPID_Speed_Para.outputNegThresh = -100;
	gPID_Speed_Para.kp0 = 0.3;
	gPID_Speed_Para.ki0 = 0.0008736;      //0.000672;    //  0.000336;
    gPID_Speed_Para.ka = 0;  //0.1 LUG DEBUG
    gPID_Speed_Para.kb = 0;  //0.1 LUG DEBUG
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
