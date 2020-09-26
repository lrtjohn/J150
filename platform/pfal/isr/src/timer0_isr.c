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

#define UPDATE_TIMER_COUNT(){                                       \
                                gTimerCnt.controlCnt++;             \
                                gTimerCnt.sciTxCnt++;               \
                                gTimerCnt.watchDogCnt++;            \
                            }

#define IS_WATCH_DOG_TIMER_EXPIRE       (gTimerCnt.watchDogCnt >= gTimerCnt.WatchDogCntThreshold)
#define IS_SCI_TX_TIMER_EXPIRE          (gTimerCnt.sciTxCnt >= gTimerCnt.sciTxCntTreshold)
#define IS_CONTROL_TIMER_TIMER_EXPIRE   (gTimerCnt.controlCnt >= gTimerCnt.controlCntTreshold)

#define RESET_WATCH_DOG_TIMER_CNT       (gTimerCnt.watchDogCnt = 0)
#define RESET_SCI_TX_TIMER_CNT          (gTimerCnt.sciTxCnt  = 0)
#define RESET_CONTROL_TIMER_TIMER_CNT   (gTimerCnt.controlCnt = 0)


TIMER_INTERVAL_CNT gTimerCnt = 
{
    0,      // watch dog
    12,     // watch dog threshold
    0,      // control 
    1,      // control threshold
    0,      // sci tx 
    4       // sci tx threshold
};

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

    if (IS_SCI_TX_TIMER_EXPIRE)
    {

#if(J150_SCI_PROTOCOL_TX == INCLUDE_FEATURE)
        RESET_SCI_TX_TIMER_CNT;
        SCI_APP_PROTOCOL_TX testData;
		memset(&testData, 0 , sizeof(testData));
#if (1)
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
        SCI_TX_SendPacket(gTxFrameArray, &testData, gScibTxQue);
#endif

#endif /* J150 SCI PROTOCOL TX */
    }
}
