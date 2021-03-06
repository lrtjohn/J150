#ifndef ECAP_SERVICE_H_
#define ECAP_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

typedef struct _ECAP_PARA
{
    Uint32 gECapCount;
    int isEcapRefresh;
    double gMotorSpeedEcap;

}ECAP_PARA;

void GetECap4Count(void);
void GetECap5Count(void);
void GetECap6Count(void);
double CalculateSpeed(Uint32 capCount);
void InitEcapVar(void);

extern ECAP_PARA gEcapPara;
#endif
