#include "timer1_isr.h"
#include "prod.h"
#include "sci_protocal.h"
#include "sci_j150.h"
#include "sci_service.h"

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimer1test = 0;
#endif

void PFAL_Timer1_ISR(void)
{
	GpioDataRegs.GPBDAT.bit.GPIO59 = 1;
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif

	/*DEBUG START*/
//	gSciAppProtocolTx_J150.RFU = spwmPara->Duty;
//	gSciAppProtocolTx_J150.RFU = gSysStateFlag.sysRunningState;
    //gSciAppProtocolTx_J150.RFU = gSysStateFlag.alarm.all;
    gSciAppProtocolTx_J150.RFU = 88;
	/*DEBUG END*/

    SCI_TX_PackData(gScibTxQue);

    CheckEnableScibTx(gScibTxQue);
//  	if (gEcapPara.isEcapRefresh == 1){
//
//		gEcapPara.gMotorSpeedEcap = CalculateSpeed(gEcapPara.gECapCount);
//		gEcapPara.isEcapRefresh = 0;
//  	}
    GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
}
