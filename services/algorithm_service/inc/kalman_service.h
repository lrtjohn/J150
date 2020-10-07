#ifndef KALMAN_SERVICE_H_
#define KALMAN_SERVICE_H_

typedef struct _KALMAN_VAR
{
    double currentData;
    double ProcessNiose_Q;
    double MeasureNoise_R;
    double xlast;
    double plast;
    int isFirstTimeExcuted;
}KALMAN_VAR;


double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R);
double KalmanVarFilter(KALMAN_VAR* kalmanVar);

extern KALMAN_VAR gKF_Speed;
void Init_gKF_Speed(void);
#endif
