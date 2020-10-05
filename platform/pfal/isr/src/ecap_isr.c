#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"
#include "ecap_isr.h"

/**************************************************************
 *Name:		   ECap1_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap1_Isr(void){
	GetECap1Count();
}
/**************************************************************
 *Name:		   ECap2_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap2_Isr(void){
	GetECap2Count();
}
/**************************************************************
 *Name:		   ECap3_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap3_Isr(void){
	GetECap3Count();
}
/**************************************************************
 *Name:		   ECap4_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap4_Isr(void){
	GetECap4Count();
}
/**************************************************************
 *Name:		   ECap5_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap5_Isr(void){
	GetECap5Count();
}
/**************************************************************
 *Name:		   ECap6_Isr
 *Comment:
 *Input:	   void
 *Output:	   void
 *Author:	   Simon
 *Date:		   2018��11��12������10:24:47
 **************************************************************/
void ECap6_Isr(void){
	GetECap6Count();
}
