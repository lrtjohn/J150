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
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif

    SCI_TX_PackData(gScibTxQue);

    CheckEnableScibTx(gScibTxQue);
//  	if (gEcapPara.isEcapRefresh == 1){
//
//		gEcapPara.gMotorSpeedEcap = CalculateSpeed(gEcapPara.gECapCount);
//		gEcapPara.isEcapRefresh = 0;
//  	}

}
