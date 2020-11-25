#include "timer1_isr.h"
#include "prod.h"
#include "sci_protocal.h"
#include "sci_j150.h"
#include "sci_service.h"
#include "ecap_service.h"
#include "spwm_service.h"

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimer1test = 0;
#endif

void PFAL_Timer1_ISR(void)
{
//	static int cnt = 0;
//	GpioDataRegs.GPBDAT.bit.GPIO59 = 1;
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif

//    if(cnt == 2){
//    	cnt = 0;
    	gSciAppProtocolTx_J150.workStatus = gSysStateFlag.j150SysStatus.all;
    	gSciAppProtocolTx_J150.sysStatus1 = gSysStateFlag.sysRunningState;
//    	gSciAppProtocolTx_J150.sysStatus2 = gSpwmPara.CloseLoopDuty;
    	gSciAppProtocolTx_J150.sysStatus2 = gSpwmPara.StepMaxDuty;
    	gSciAppProtocolTx_J150.faultStatus = gSysStateFlag.alarm.all;
//    	gSciAppProtocolTx_J150.targetSpeed = gSciAppProtocolRx_J150.targetSpeed;
    	gSciAppProtocolTx_J150.targetSpeed = gSpwmPara.TargetDuty;
//    	gSciAppProtocolTx_J150.targetSpeed = gSpwmPara.StepMaxDuty;
    	gSciAppProtocolTx_J150.currentSpeed = gEcapPara.gMotorSpeedEcap;
//    	gSciAppProtocolTx_J150.targetSpeed = gSpwmPara.Duty_Gradual;
    	gSciAppProtocolTx_J150.busVoltage = gSysAnalogVar.single.var[updatePower270V_M].value;
//    	gSciAppProtocolTx_J150.busVoltage = gCurrent_Struct.I_bridgeABC[0];
    	gSciAppProtocolTx_J150.busCurrent = gCurrent_Struct.I_busCurrent_Ave;
    	gSciAppProtocolTx_J150.servoTemp = gSysAnalogVar.single.var[updateDriverTemp].value;
    	gSciAppProtocolTx_J150.motorTemp = gSysAnalogVar.single.var[updateMotorTemp].value;
//    	gSciAppProtocolTx_J150.fwVersionNum = gSysVersionNum;
    	gSciAppProtocolTx_J150.fwVersionNum = gCurrent_Struct.Max_BusCurrent;

//    	gSciAppProtocolTx_J150.workMode = gSysStateFlag.j150WorkMode;
    	gSciAppProtocolTx_J150.workMode = gSpwmPara.restrictduty;
    	gSciAppProtocolTx_J150.RFU = gSpwmPara.Duty_Gradual;
//    	gSciAppProtocolTx_J150.RFU = (Uint16)(gPID_Speed_Para.sumErr * gPID_Speed_Para.ki);


        SCI_TX_PackData(gScibTxQue);

        CheckEnableScibTx(gScibTxQue);
//    }
//    else{
//    	++cnt;
//    }
	/*DEBUG START*/
//	gSciAppProtocolTx_J150.RFU = gSysStateFlag.rotateDirectoin;
//	gSciAppProtocolTx_J150.currentSpeed = gCurrent_Struct.zero_IABC[0];
//	gSciAppProtocolTx_J150.RFU = gSysStateFlag.sysRunningState;
//    gSciAppProtocolTx_J150.RFU = gSysStateFlag.alarm.all;
//	gSciAppProtocolTx_J150.RFU = gCurrent_Struct.zero_IABC[1];
	/*DEBUG END*/


//    GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
}
