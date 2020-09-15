#include "pid_service.h"

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
