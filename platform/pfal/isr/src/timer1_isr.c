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
//	GpioDataRegs.GPBDAT.bit.GPIO59 = 1;
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif

	gSciAppProtocolTx_J150.workStatus = gSysStateFlag.j150SysStatus.all;
	gSciAppProtocolTx_J150.sysStatus1 = gSysStateFlag.sysRunningState;
	gSciAppProtocolTx_J150.sysStatus2 = gSpwmPara.StepMaxDuty;
	gSciAppProtocolTx_J150.faultStatus = gSysStateFlag.j150CustAlarm.all;
	gSciAppProtocolTx_J150.frameCnt = gSciAppProtocolTx_J150.frameCnt + 1;
	gSciAppProtocolTx_J150.targetSpeed = gSciAppProtocolRx_J150.targetSpeed;
	gSciAppProtocolTx_J150.currentSpeed = gEcapPara.gMotorSpeedEcap;
	gSciAppProtocolTx_J150.busVoltage = (Uint16)((double)(gSysAnalogVar.single.var[updatePower270V_M].value) * BUSVOLTAGE_K + BUSVOLTAGE_B);
	gSciAppProtocolTx_J150.busCurrent = (Uint16)((double)(gCurrent_Struct.I_busCurrent_Ave) * BUSCURRENT_K + BUSCURRENT_B);
	gSciAppProtocolTx_J150.servoTemp = (Uint16)((double)(gSysAnalogVar.single.var[updateDriverTemp].value) * SERVO_TEMP_K + SERVO_TEMP_B);
	gSciAppProtocolTx_J150.motorTemp = (Uint16)((double)(gSysAnalogVar.single.var[updateMotorTemp].value) * MOTOR_TEMP_K + MOTOR_TEMP_B);
	gSciAppProtocolTx_J150.fwVersionNum = gSysVersionNum;
//    	gSciAppProtocolTx_J150.workMode = gSysStateFlag.j150WorkMode;
	gSciAppProtocolTx_J150.workMode = gSpwmPara.restrictduty;
	gSciAppProtocolTx_J150.RFU = gSpwmPara.Duty;

	SCI_TX_PackData(gScibTxQue);

	CheckEnableScibTx(gScibTxQue);

//    GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
}
