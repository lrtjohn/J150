#include "pid_service.h"
#include "spwm_service.h"
#include "kalman_service.h"
PID_VAR gPID_Speed_Para = {0};
OPENLOOP_VAR gOpenLoop_Para = {0};

#define COMPENSATE_DUTY_K	(0.36) //0.36 LUG DEBUG
#define K_KPN				(0.0002833)
#define B_KPN				(-0.1333)
#define K_KPE				(0.002222)
#define B_KPE				(0.7778)
#define K_KIN				(0.0004833)
#define B_KIN				(-0.1833)
#define K_SKE				(-0.001111)
#define B_SKE				(1.111)

#define K_KQN				(0.0002667)
#define B_KQN				(-0.06667)

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
	double kqn = 0;

    gKF_Current.currentData = gCurrent_Struct.I_bus_RBUF_Sum >> 8;//7
    gCurrent_Struct.I_busCurrent_Ave = KalmanVarFilter(&gKF_Current);

    kqn = K_KQN * gPID_Speed_Para.targetVal + B_KQN;
    if(kqn > 1) kqn = 1;
    else if (kqn < 0.2) kqn = 0.2;
    else;
	I_busCurrent = gCurrent_Struct.I_busCurrent_Ave;
	if(I_busCurrent < 62) I_busCurrent = 0;
	else if(I_busCurrent > 1000) I_busCurrent = 1000;
	else; /*DO NOTHING*/
	Compensate_Duty = I_busCurrent * COMPENSATE_DUTY_K * 0.15 * gOpenLoop_Para.volt_Ratio * kqn;//0.6;   // 0.805;
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
    double kp_ratio = 0;
    double absCurrentErr = 0;

    pidVar->kpn = K_KPN * pidVar->targetVal + B_KPN;
    if(pidVar->kpn > 1) pidVar->kpn = 1;
    else if (pidVar->kpn < 0.15) pidVar->kpn = 0.15;
    else;
    pidVar->kin = K_KIN * pidVar->targetVal + B_KIN;
    if(pidVar->kin > 1.75) pidVar->kin = 1.75;
    else if (pidVar->kin < 0.3) pidVar->kin = 0.3;
    else;
    pidVar->currentErr = (pidVar->targetVal - (pidVar->currentVal));
    if(pidVar->currentErr < 0) absCurrentErr = -(pidVar->currentErr);
    if(absCurrentErr < 100) absCurrentErr = 100;
    if(absCurrentErr > 1000) absCurrentErr = 1000;

    pidVar->kpe = K_KPE * absCurrentErr + B_KPE;
    if(pidVar->kpe > 3) pidVar->kpe = 3;
    else if (pidVar->kpe < 1) pidVar->kpe = 1;
    else;
    pidVar->ske = K_SKE * absCurrentErr + B_SKE;
    if(pidVar->ske > 1) pidVar->ske = 1;
    else if (pidVar->ske < 0) pidVar->ske = 0;
    else;

    if((pidVar->currentErr > -(pidVar->currentErrThreshold)) && (pidVar->currentErr < pidVar->currentErrThreshold))
    {
    	kp_ratio = 1;
		if((( pidVar->currentErr > 0) && (pidVar->sumErr < pidVar->sumErrThreshold)) || ((pidVar->currentErr < 0) && (pidVar->sumErr > -pidVar->sumErrThreshold)))
		{
			pidVar->sumErr = pidVar->sumErr + (pidVar->currentErr * pidVar->ske);
		}
    }
    else
    {
    	kp_ratio = 0;
        pidVar->sumErr = 0;
    }
    
    kp = pidVar->kp0 * pidVar->kpe * pidVar->kpn * gOpenLoop_Para.volt_Ratio;
    ki = pidVar->ki0 * pidVar->kin * gOpenLoop_Para.volt_Ratio;

    pidOutput = (int)(pidVar->currentErr * kp * kp_ratio) + (int)(pidVar->sumErr * ki);

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
	gPID_Speed_Para.currentErrThreshold = 2000;//600;//350;
	gPID_Speed_Para.sumErrThreshold = 801283;//457876;//228938;    //1050000;   // 2100000;
	gPID_Speed_Para.outputPosThresh = 1100;
	gPID_Speed_Para.outputNegThresh =-400; //-100;
	gPID_Speed_Para.kp0 = 0.3;
	gPID_Speed_Para.ki0 =0.0024;//0.0006;          //0.0002184;      //0.000672;    //  0.000336;
    gPID_Speed_Para.kpe = 0;  //0.1 LUG DEBUG
    gPID_Speed_Para.kpn = 0;  //0.1 LUG DEBUG
    gPID_Speed_Para.kin = 0;
    gPID_Speed_Para.ske = 0;
}

void Init_OpenLoop_Service(void)
{
	gOpenLoop_Para.currentBusVoltage = 0;
	gOpenLoop_Para.nominalBusVoltage = 2585;
	gOpenLoop_Para.volt_Ratio = 0.794;
	gOpenLoop_Para.targetSpeed = 0;
	gOpenLoop_Para.openloop_K = 0.2;  //0.21774;//0.2292;
	gOpenLoop_Para.openloop_B = -10;//-123.83;
}
