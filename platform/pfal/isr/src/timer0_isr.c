#include "timer0_isr.h"
#include "prod.h"
#include "gpio_service.h"
#include "sci_protocal.h"
#include <string.h>

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimertest = 0;
#endif

/* Interval unit: ms */
#define TIME_BASE_INTERVAL  (5)
#define TIME_SCI_TX_INTERVAL            (20 / TIME_BASE_INTERVAL)
#define TIME_FEED_WATCH_DOG_INTERVAL    (60 / TIME_BASE_INTERVAL)

TIMER_INTERVAL_CNT gTimerCnt = 
{
    0,      // watch dog
    12,     // watch dog threshold
    0,      // control 
    1,      // control threshold
    0,      // sci tx 
    4       // sci tx threshold
};

#define UPDATE_TIMER_COUNT(){                                           \
                                gTimerCnt.controlCnt++;          \
                                gTimerCnt.sciTxCnt++;            \
                                gTimerCnt.watchDogCnt++;     \
                            }
#define IS_WATCH_DOG_TIMER_EXPIRE       (gTimerCnt.watchDogCnt >= gTimerCnt.WatchDogCntThreshold)
#define IS_SCI_TX_TIMER_EXPIRE          (gTimerCnt.sciTxCnt >= gTimerCnt.sciTxCntTreshold)
#define IS_CONTROL_TIMER_TIMER_EXPIRE   (gTimerCnt.controlCnt >= gTimerCnt.controlCntTreshold)

#define RESET_WATCH_DOG_TIMER_CNT       (gTimerCnt.watchDogCnt = 0)
#define RESET_SCI_TX_TIMER_CNT          (gTimerCnt.sciTxCnt  = 0)
#define RESET_CONTROL_TIMER_TIMER_CNT   (gTimerCnt.controlCnt = 0)

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


void PFAL_Timer0_ISR(void)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimertest++;
#endif
    UPDATE_TIMER_COUNT();

    if (IS_CONTROL_TIMER_TIMER_EXPIRE)
    {
        RESET_CONTROL_TIMER_TIMER_CNT;
    }

    if (IS_WATCH_DOG_TIMER_EXPIRE)
    {
        RESET_WATCH_DOG_TIMER_CNT;

        TOOGLE_CTL_BOARD_WATCHDOG;
	    TOOGLE_DRIVE_BOARD_WATCHDOG;
    }
    //PackSciTxPacket(gScibTxQue,gSciTxVar);
    if (IS_SCI_TX_TIMER_EXPIRE)
    {
        RESET_SCI_TX_TIMER_CNT;
        SCI_APP_PROTOCOL_TX testData;
		memset(&testData, 0 , sizeof(testData));
#if (0)
        testData.txHead1        = 0x55;
        testData.txHead2        = 0x55;
        testData.txLength       = 33;
        testData.workStatus     = 0x1234;
        testData.sysStatus1     = 0x5678;
        testData.sysStatus2     = 0x9012;
        testData.faultStatus    = 0x44332211;
        testData.frameCnt       = 0x55667788;
        testData.targetSpeed    = 0x3344;
        testData.currentSpeed   = 0x3344;
        testData.busVoltage     = 0x7788;
        testData.busCurrent     = 0x1122;
        testData.servoTemp      = 0x09;
        testData.motorTemp      = 0x08;
        testData.fwVersionNum   = 0x00;
        testData.workMode       = 0x82;
        testData.RFU            = 0x9999;
#endif
        testData.txHead1        = 0x55;
        testData.txHead2        = 0x55;
        testData.txLength       = 33;
        testData.workStatus     = 0x0;
        testData.sysStatus1     = 0x0;
        testData.sysStatus2     = 0x0;
        testData.faultStatus    = 0x0;
        testData.frameCnt       = 0x0;
        testData.targetSpeed    = 0x0;
        testData.currentSpeed   = 0x0;
        testData.busVoltage     = 0x0;
        testData.busCurrent     = 0x0;
        testData.servoTemp      = 0x0;
        testData.motorTemp      = 0x88;
        testData.fwVersionNum   = 0x00;
        testData.workMode       = 0x82;
        testData.RFU            = 0x0;

        SCI_TX_SendPacket(gTxFrameArray, &testData, gScibTxQue);
    }
   //SimulateSSI();
}
