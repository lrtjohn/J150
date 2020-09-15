#include "position_ssi_service.h"

POSITION_SSI_PARA gPositionSSIPara = {0};

void PositionSSIService(void)
{
    static int count = 0;
    static int subWait = 0;
    Uint32 tmp = 0;
    static Uint32 gSSIDATA = 0;

    if(count == 0)
    {
        GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
        count++;
        gSSIDATA = 0;
        
        return;
    }

    if(count == 1)
    {
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;
        count++;
        return;
    }

    if(count == (gPositionSSIPara.sensorBit * 2 + 1))
    {
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;

        if(subWait++ > gPositionSSIPara.subWaitTimes)
        {
            gPositionSSIPara.currentPos = gSSIDATA >> 1;
            subWait = 0;
            count = 0;
        }
        return;
    }

    if((count % 2) == 0)
    {
        tmp = GpioDataRegs.GPBDAT.bit.GPIO62;
        gSSIDATA |= (tmp << (17 - (count/2)));
        GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
        count++;
        return;
    }

    if((count % 2) == 1)
    {
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;
        count++;
        return;
    }   
}

void Init_PositionSSI_Service(void)
{
    gPositionSSIPara.currentPos = 0;
    gPositionSSIPara.isFirstExecuted = 1;
    gPositionSSIPara.lastPos = 0;
    gPositionSSIPara.powerUpPos = 0;
    gPositionSSIPara.sensorBit = 16;
    gPositionSSIPara.subWaitTimes = 60;
    gPositionSSIPara.totalDistance = 0;
}

