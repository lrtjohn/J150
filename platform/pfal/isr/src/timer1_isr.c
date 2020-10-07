#include "timer1_isr.h"
#include "ecap_service.h"
#include "kalman_service.h"
#include "prod.h"


#if(SYS_DEBUG == INCLUDE_FEATURE)
int gtimer1test = 0;
#endif

void MotorSpeed(){
	static int count = 0;
//	int calSpeed = -1;

  	if (gEcapPara.isEcapRefresh == 1){

  		gKF_Speed.currentData = CalculateSpeed(gEcapPara.gECapCount);
		if(gKF_Speed.currentData != -1){
			gEcapPara.gMotorSpeedEcap = KalmanVarFilter(&gKF_Speed);
		}
		gEcapPara.isEcapRefresh = 0;
		count = 0;
  	}
  	else{
		count++;
		if(count > 5){
			gKF_Speed.currentData = 0;
			gEcapPara.gMotorSpeedEcap = KalmanVarFilter(&gKF_Speed);
			count = 0;
		}
  	}
}

void PFAL_Timer1_ISR(void)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
    gtimer1test++;
#endif
    MotorSpeed();

//  	if (gEcapPara.isEcapRefresh == 1){
//
//		gEcapPara.gMotorSpeedEcap = CalculateSpeed(gEcapPara.gECapCount);
//		gEcapPara.isEcapRefresh = 0;
//  	}

}
