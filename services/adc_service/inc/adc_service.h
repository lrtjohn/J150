#ifndef ADC_SERVICE_H_
#define ADC_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "adc_hal.h"
#include "sys_state_service.h"

#define BUSVOLTAGE_K (0.1038)//(0.106)//(0.1047)
#define BUSVOLTAGE_B (0.8954)//(0.68314)//(-0.7154)
#define BUSCURRENT_K (0.02896)//(0.0295)
#define BUSCURRENT_B (0.6442)//(0.1709)
#define SERVO_TEMP_K (0.026367)
#define SERVO_TEMP_B (27.738)
#define MOTOR_TEMP_K (0.06265)
#define MOTOR_TEMP_B (-64.6605)

//single ADC channel
enum SNGL_ANAL_IDX
{
	updateBridgeCurrentB = 0,		//0  X_IAB_3V3AN
	updateBridgeCurrentC,		    //1  X_ICD_3V3AN
	updateBridgeCurrentA,			//2 Y_ICD_3V3AN
	updateCurrentMin,		    	//3 Z_ICD_3V3AN
	updateDriverTemp,	        	//4 Z_IAB_3V3AN
	updateVoltageRef1V5,			//5 VBUS_AN3V3
	updatePower270V_M,		    	//6 Y_IAB_3V3AN
	updateDriverVoltage5V,		    //7 T1V9_ISEN_AN
	Reversed_chl5,	        		//8 T1V9V_TEMP_AN
	updateCurrentMax,		   	 	//9 VDD3V3_ISEN_AN
	updateVoltage28V,         		//10 VDD3V3_TEMP_AN
	updateVoltageRef2V5,		    //11 ADCINB4
	updateCurrent28V,               //12 ADCINB5
	updateVoltageAVDD5V,         	//13 VCC3V3_ISEN_AN
	updateMotorTemp,         		//14 VCC3V3_TEMP_AN
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

typedef struct _Current_Struct{
	Uint32 zerosum_IABC[3];
	Uint16 zero_IABC[3];
	int16 I_bridgeABC[3];
	int16 Thr_max_I_Bridge;
	int16 Thr_min_I_Bridge;
	int16 Thr_max_I_Bus;
	int16 Thr_min_I_Bus;
	int16 I_busCurrent;
	int16 I_bridgeSum;
	int16 Thr_BridgeSum;
	int16 Thr_BusCurrent;
	int16 cnt_max_threshold[3];
	int16 Pos_BridgeCurrent[3];
	int16 Neg_BridgeCurrent[3];
	int16 Pos_BridgeSum;
	int16 Neg_BridgeSum;
	int16 Max_BusCurrent;
	int16 I_busCurrent_Ave;
	int32 I_bus_RBUF_Sum;
}Current_Struct;

typedef struct _Voltage_Struct{
	Uint16 Thr_max_Voltage;
	Uint16 Thr_max2nd_Voltage;
	Uint16 Thr_max3rd_Voltage;
	Uint16 Thr_max4th_Voltage;
	Uint16 Thr_min_Voltage;
	Uint16 Thr_min2nd_Voltage;
}Voltage_Struct;

typedef struct _Temperature_Struct{
	Uint16 Thr_max_warning_motor_Temp;
	Uint16 Thr_max2nd_warning_motor_Temp;
	Uint16 Thr_max_alarm_motor_Temp;
	Uint16 Thr_max2nd_alarm_motor_Temp;

	Uint16 Thr_max_warning_driver_Temp;
	Uint16 Thr_max2nd_warning_driver_Temp;
	Uint16 Thr_max_alarm_driver_Temp;
	Uint16 Thr_max2nd_alarm_driver_Temp;
}Temperature_Struct;

typedef struct _Analog_Ref_Struct{
	Uint16 analog_ref[7];
	Uint16 thr_max_analog_ref[7];
	Uint16 thr_min_analog_ref[7];
	Uint16 cnt_analog_ref[7];
}Analog_Ref_Struct;

void Init_Adc_Service(void);
void UpdateSingleAnalog(SysAnalogVar* sysAnalogVar);
void PwrBus_OverVoltage_BIT(void);
void BridgeABC_Current_Monitor_BIT(void);
void CheckMotorTemperature(void);
void CheckDriverTemperature(void);
void check_28V_Current(void);
void check_28V_Voltage(void);
void check_VCC5V(void);
void check_AVDD5V(void);
void check_Ref2V5(void);
void check_CurrentMax(void);
void check_Driver5V(void);
void check_Ref1V5(void);
void check_CurrentMin(void);
void Init_ADC_Current(void);
void Init_ADC_Voltage(void);
void Init_ADC_Temperature(void);
void Init_Analog_Ref(void);
void check_Analog_Ref(void);
extern SysAnalogVar gSysAnalogVar;
extern Current_Struct gCurrent_Struct;
extern Voltage_Struct gVoltage_Struct;
extern Temperature_Struct gTemperature_Struct;
extern Analog_Ref_Struct gAnalog_Ref_Struct;
#endif
