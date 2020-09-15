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
    double outputThreshold;
    double kp;
    double ki;
}PID_VAR;

#endif
