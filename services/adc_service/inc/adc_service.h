#ifndef ADC_SERVICE_H_
#define ADC_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "adc_hal.h"
//single ADC channel
enum SNGL_ANAL_IDX
{
	updateBridgeCurrentB = 0,		//0  X_IAB_3V3AN
	updateBridgeCurrentC,		    //1  X_ICD_3V3AN
	updateBridgeCurrentA,			//2 Y_ICD_3V3AN
	updateCurrentMin,		    //3 Z_ICD_3V3AN
	updateDriverTemp,	        //4 Z_IAB_3V3AN
	updateVoltageRef1V5,			    //5 VBUS_AN3V3
	updatePower270V_M,		    //6 Y_IAB_3V3AN
	updateDriverVoltage5V,		    //7 T1V9_ISEN_AN
	Reversed_chl5,	        //8 T1V9V_TEMP_AN
	updateCurrentMax,		    //9 VDD3V3_ISEN_AN
	updateVoltage28V,         //10 VDD3V3_TEMP_AN
	updateVoltageRef2V5,		        //11 ADCINB4
	updateCurrent28V,                //12 ADCINB5
	updateVoltageAVDD5V,         //13 VCC3V3_ISEN_AN
	updateMotorTemp,         //14 VCC3V3_TEMP_AN
	updateVoltageVCC5V,
    TOTAL_SNGL_ANAL_CHS
};
//multi ADC channel
enum MULTI_ANAL_IDX
{
	BIT1_AN_COM = 0,		//0  X_IAB_3V3AN
    TOTAL_MULTI_ANAL_CHS
};
//multi ADC sub channel
enum MULTI_ANAL_SUB_IDX
{
	X_T1_3V3AN = 0,		//0  X_IAB_3V3AN
	X_T2_3V3AN,		    //1  X_ICD_3V3AN
	BIT_REF_2V3,			//2 Y_ICD_3V3AN
	Y_T2_3V3AN,		    //3 Z_ICD_3V3AN
	Y_T1_3V3AN,	        //4 Z_IAB_3V3AN
	Z_T2_3V3_AN,			    //5 VBUS_AN3V3
	I_QDDCDC_AN3V3,		    //6 Y_IAB_3V3AN
	Z_T1_3V3AN,		    //7 T1V9_ISEN_AN       //VCC3V3_TEMP_AN
    TOTAL_MULTI_ANAL_SUB_CHS
};

typedef Uint16 (*UV)(void);
typedef struct _AnalogVar{
	Uint16 value;

	Uint16 max;
	Uint16 max2nd;
    Uint16 min2nd;
	Uint16 min;

	int count_max;
	int count_min;
	UV updateValue;
}AnalogVar;

typedef struct _SingleChannelA{
	AnalogVar var[TOTAL_SNGL_ANAL_CHS];
}SingleChannelA;
typedef Uint16 (*SwitchCh)(void);
typedef struct _MultiChannelA{
	AnalogVar   var[TOTAL_MULTI_ANAL_SUB_CHS];
    SwitchCh    switchChannel; 
}MultiChannelA;

typedef struct _SysAnalogVar{
	SingleChannelA single;
	MultiChannelA multi[TOTAL_MULTI_ANAL_CHS];
}SysAnalogVar;

void Init_Adc_Service_Ptr(SysAnalogVar* sysAnalogVar);
void Init_Adc_Service(void);
extern SysAnalogVar gSysAnalogVar;
#endif
