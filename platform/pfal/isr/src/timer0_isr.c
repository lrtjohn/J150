#include "timer0_isr.h"
#include "prod.h"
#include "gpio_service.h"

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimertest = 0;
#endif

Uint32 gSSIDATA = 0;
Uint32 gSSIDATABAK = 0;

void SimulateSSI(void)
{
    static int count = 0;
    static int subWait = 0;
    Uint32 tmp = 0;

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

    if(count == 33)
    {
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;

        if(subWait++ > 60)
        {
            gSSIDATABAK = gSSIDATA >> 1;
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

int gFeedWatchDogCnt = 0;
void PFAL_Timer0_ISR(void)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimertest++;
#endif
    static Uint64 count = 0;
    count++;
    if(count > 3)
    {
        count = 0;
        gFeedWatchDogCnt++;
        TOOGLE_CTL_BOARD_WATCHDOG;
	    TOOGLE_DRIVE_BOARD_WATCHDOG;
    }

    //SimulateSSI();
}
