#include "ecap_service.h"
#include "sys_state_service.h"
ECAP_PARA gEcapPara = {0};

void InitEcapVar(void){
	gEcapPara.gMotorSpeedEcap = 0;
	gEcapPara.isEcapRefresh = 0;
	gEcapPara.gECapCount = 0;
	gEcapPara.SpeedUpperProtectLimit = 5500;
	gEcapPara.SpeedLowerProtectLimit = 5300;
	gEcapPara.SpeedUpperWarnLimit = 5100;
	gEcapPara.SpeedLowerWarnLimit = 4900;
//    gECapCount = 0;
}

/**************************************************************
 *Name:		   CalculateSpeed
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018��11��12������10:27:17
 **************************************************************/
double CalculateSpeed(Uint32 capCount){
	//TODO calculate the motor speed
	double speed32 = 0;
//	if(capCount <= 0){
//		return -1;
//	}

	//unit of speed32 = degree/sec
	//6171428571.42857
	//1436156.641641
//	speed32 = (((CPU_FREQUENCY * 60000000) / MOTOR_POLES)/(float)capCount);//1800000000 = 150000000*60/5 150000000=150MHz pwm clk, 5=the nunber of pairs of poles of the motor
	speed32 = (1800000000/(float)capCount);
	return speed32;
//	if(speed32 < 19200){
//		return speed32;
//	}
//	else{
//		return -1;
//	}
}

void checkMotorSpeed (void){
    static int cnt_alarm_max = 0;
    static int cnt_alarm_max2nd = 0;
    static int over_alarm_limit_lasttime = 0;

    static int cnt_warn_max = 0;
    static int cnt_warn_max2nd = 0;
    static int over_warn_limit_lasttime = 0;

    if(over_alarm_limit_lasttime == 1){
        if(gEcapPara.gMotorSpeedEcap < gEcapPara.SpeedLowerProtectLimit){
            ++cnt_alarm_max2nd;
            if(cnt_alarm_max2nd >300){
            	CLEAR_MOTOR_OVER_SPEED_ALARM;
            	CLEAR_MOTOR_SPEED_PROT;
            	over_alarm_limit_lasttime = 0;
            }
        }
        else{
        	cnt_alarm_max2nd = 0;
            over_alarm_limit_lasttime = 1;
            SET_MOTOR_OVER_SPEED_ALARM;
            SET_MOTOR_SPEED_PROT;
        }
    }
    else if (over_alarm_limit_lasttime == 0){
        if(gEcapPara.gMotorSpeedEcap > gEcapPara.SpeedUpperProtectLimit) {
            ++cnt_alarm_max;
            if(cnt_alarm_max > 300){
                cnt_alarm_max = 0;
                SET_MOTOR_OVER_SPEED_ALARM;
                SET_MOTOR_SPEED_PROT;
                over_alarm_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_alarm_max >= 1) --cnt_alarm_max;
            else cnt_alarm_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }

    if(over_warn_limit_lasttime == 1){
        if(gEcapPara.gMotorSpeedEcap < gEcapPara.SpeedLowerWarnLimit){
            ++cnt_warn_max2nd;
            if(cnt_warn_max2nd >300){
            	CLEAR_BUS_OVER_VOLT_WARN;
            	over_warn_limit_lasttime = 0;
            }
        }
        else{
        	cnt_warn_max2nd = 0;
        	over_warn_limit_lasttime = 1;
        	SET_BUS_OVER_VOLT_WARN;
        }
    }
    else if (over_warn_limit_lasttime == 0){
        if(gEcapPara.gMotorSpeedEcap > gEcapPara.SpeedUpperWarnLimit) {
            ++cnt_warn_max;
            if(cnt_warn_max > 300){
            	cnt_warn_max = 0;
            	SET_BUS_OVER_VOLT_WARN;
                over_warn_limit_lasttime = 1;
            }
        }
        else{
            if(cnt_warn_max >= 1) --cnt_warn_max;
            else cnt_warn_max = 0;
        }
    }
    else{
//    	gSysSWAlarm.bit.updateAndCheckTemperature = 1;
//    	gSysAlarm.bit.softwareFault = 1;
    }
}

/**************************************************************
 *Name:		   GetECap2Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap2Count(void){

	if(ECap2Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap2Regs.CAP2 - ECap2Regs.CAP1;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap2Regs.CAP3 - ECap2Regs.CAP2;
	}
	else if(ECap2Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap2Regs.CAP4 - ECap2Regs.CAP3;
	}
	else{

	}
}

/**************************************************************
 *Name:		   GetECap4Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap3Count(void){

	if(ECap3Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap3Regs.CAP2 - ECap3Regs.CAP1;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap3Regs.CAP3 - ECap3Regs.CAP2;
	}
	else if(ECap3Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap3Regs.CAP4 - ECap3Regs.CAP3;
	}
	else{

	}
}

/**************************************************************
 *Name:		   GetECap4Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap4Count(void){

	if(ECap4Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap4Regs.CAP1;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap4Regs.CAP2 - ECap4Regs.CAP1;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap4Regs.CAP3 - ECap4Regs.CAP2;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap4Regs.CAP4 - ECap4Regs.CAP3;
	}
	else{

	}
}
