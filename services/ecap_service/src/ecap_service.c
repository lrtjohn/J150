#include "ecap_service.h"
ECAP_PARA gEcapPara = {0};

void InitEcapVar(void){
	gEcapPara.gMotorSpeedEcap = 0;
	gEcapPara.isEcapRefresh = 0;
	gEcapPara.gECapCount = 0;
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
	speed32 = ((201061.9298297)/(float)capCount);//17142857.142857 = 120000000/7 120000000=120MHz clk, 7=the nunber of pairs of poles of the motor
	return speed32;
//	if(speed32 < 19200){
//		return speed32;
//	}
//	else{
//		return -1;
//	}
}

/**************************************************************
 *Name:		   GetECap1Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap1Count(void){

	if(ECap1Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap1Regs.CAP1;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap1Regs.CAP2 - ECap1Regs.CAP1;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap1Regs.CAP3 - ECap1Regs.CAP2;
	}
	else if(ECap1Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap1Regs.CAP4 - ECap1Regs.CAP3;
	}
	else{

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
/**************************************************************
 *Name:		   GetECap5Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap5Count(void){

	if(ECap5Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap5Regs.CAP1;
	}
	else if(ECap5Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap5Regs.CAP2 - ECap5Regs.CAP1;
	}
	else if(ECap5Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap5Regs.CAP3 - ECap5Regs.CAP2;
	}
	else if(ECap4Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap5Regs.CAP4 - ECap5Regs.CAP3;
	}
	else{

	}
}
/**************************************************************
 *Name:		   GetECap6Count
 *Comment:
 *Input:	   void
 *Output:	   motor speed(int)
 *Author:	   Simon
 *Date:		   2018.11.14
 **************************************************************/
void GetECap6Count(void){

	if(ECap6Regs.ECFLG.bit.CEVT1){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap6Regs.CAP1;
	}
	else if(ECap6Regs.ECFLG.bit.CEVT2){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap6Regs.CAP2 - ECap6Regs.CAP1;
	}
	else if(ECap6Regs.ECFLG.bit.CEVT3){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap6Regs.CAP3 - ECap6Regs.CAP2;
	}
	else if(ECap6Regs.ECFLG.bit.CEVT4){
		gEcapPara.isEcapRefresh = 1;
	    gEcapPara.gECapCount = ECap6Regs.CAP4 - ECap6Regs.CAP3;
	}
	else{

	}
}
