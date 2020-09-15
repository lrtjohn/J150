#ifndef POSITION_SSI_SERVICE_H_
#define POSITION_SSI_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"

typedef struct
{
    int64 powerUpPos;
    int64 currentPos;
    int64 lastPos;
    int64 totalDistance;
    int64 sensorBit;
    int64 subWaitTimes;
    Uint16 isFirstExecuted;
}POSITION_SSI_PARA;

void Init_PositionSSI_Service(void);
#endif
