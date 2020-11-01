#ifndef SYS_STATE_SERVICE_H_
#define SYS_STATE_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod_defs.h"

typedef struct{
	Uint16 high8bit : 8;
	Uint16 low8bit	: 8;
}VAR16BIT;

typedef struct{
	Uint16 high16bit : 16;
	Uint16 low16bit	 : 16;
}VAR32BIT;

typedef struct _ERROR_16BIT
{
	Uint16 software : 1;
	Uint16 init : 1;
	Uint16 temperature : 1;
	Uint16 busVoltage : 1;
	Uint16 busCurrent : 1;
	Uint16 hardware : 1;
	Uint16 memoryFull : 1;
	Uint16 rxQFull : 1;
	Uint16 txQFull : 1;
	Uint16 j : 1;
	Uint16 k : 1;
	Uint16 l : 1;
	Uint16 m : 1;
	Uint16 n : 1;
	Uint16 o : 1;
	Uint16 p : 1;
}ERROR_16BIT;

typedef struct _ALARM_32BIT
{
	Uint16 software     : 1;/*0*/
	Uint16 init         : 1;/*1 暂未使用*/
	Uint16 motortemp    : 1;/*2*/
	Uint16 busUV        : 1;/*3*/
	Uint16 busOV		: 1;/*4*/
	Uint16 busCurrent   : 1;/*5*/
	Uint16 hardware     : 1;/*6*/
	Uint16 pgVcc5V      : 1;/*7*/
	Uint16 pg1v9        : 1;/*8*/
	Uint16 pgVcc3V3     : 1;/*9*/
	Uint16 pgVdd5V      : 1;/*10*/
	Uint16 drivertemp   : 1;/*11*/
	Uint16 bridgeCurrent: 1;/*12*/
	Uint16 swbusCurrent : 1;/*13*/
	Uint16 bridgeSum    : 1;/*14*/
	Uint16 swbusOV      : 1;/*15*/
	Uint16 ctrlbusVolt	: 1;/*16*/
	Uint16 ctrlbusCurr  : 1;/*17*/
	Uint16 overspeed    : 1;/*18*/
	Uint16 hw_digit_sig : 1;/*19 PG*/
	Uint16 hw_digit_lvl	: 1;/*20*/
	Uint16 hw_anlg_lvl	: 1;/*21 other ADs except 270V V and I*/
	Uint16 hw_I_zero	: 1;/*22*/
	Uint16 sw_pwm_alarm : 1;/*23 来自PWM报警*/
	Uint16 i        	: 1;/*24*/
	Uint16 j     		: 1;/*25*/
	Uint16 k      		: 1;/*26*/
	Uint16 l   			: 1;/*27*/
	Uint16 m 			: 1;/*28*/
	Uint16 n 			: 1;/*29*/
	Uint16 o    		: 1;/*30*/
	Uint16 p      		: 1;/*31*/
}ALARM_32BIT;

typedef struct _WARINING_16BIT
{
	Uint16 software     : 1;
	Uint16 init         : 1;
	Uint16 motortemp  	: 1;
	Uint16 busVoltage   : 1;
	Uint16 busCurrent   : 1;
	Uint16 hardware     : 1;
	Uint16 drivertemp 	: 1;
	Uint16 h : 1;
	Uint16 i : 1;
	Uint16 j : 1;
	Uint16 k : 1;
	Uint16 l : 1;
	Uint16 m : 1;
	Uint16 n : 1;
	Uint16 o : 1;
	Uint16 p : 1;
}WARINING_16BIT;

typedef struct _SYS_STATUS_16BIT
{
	Uint16 BIT_CMPLT	: 1;
	Uint16 POWER_BUS    : 1;
	Uint16 FAULT_EXT	: 1;
	Uint16 MOTOR_STA    : 1;
	Uint16 e			: 1;
	Uint16 f   			: 1;
	Uint16 g     		: 1;
	Uint16 h      		: 1;
	Uint16 i       		: 1;
	Uint16 j     		: 1;
	Uint16 k            : 1;
	Uint16 l            : 1;
	Uint16 m            : 1;
	Uint16 n            : 1;
	Uint16 o            : 1;
	Uint16 p            : 1;
}SYS_STATUS_16BIT;

typedef union
{
	Uint16          all;
	VAR16BIT        data;
	ERROR_16BIT     bit;
}SYSERRO;

typedef union
{
	Uint16          all;
	VAR16BIT        data;
	WARINING_16BIT  bit;
}SYSWARNING;

typedef union
{
	Uint32          all;
	VAR32BIT        data;
	ALARM_32BIT  	bit;
}SYSALARM;

typedef enum _ROTATE_DIRECTION
{
    STOP,
    FORWARD
}ROTATE_DIRECTION;

typedef enum _WORK_MODE
{
    NORMAL,
    BATTLE
}J150_WORK_MODE;

typedef enum _SYS_RUNNING_STATE
{
    SYS_INIT,
    SYS_FORWARD_RUN,
    SYS_STOP,
    SYS_ALARM
}SYS_RUNNING_STATE;

typedef union
{
	Uint16          	all;
	VAR16BIT        	data;
	SYS_STATUS_16BIT    bit;
}J150_SYS_STATUS;

typedef struct _J150_SYS_INFO
{
	/* Just add this data structure in case some special info for J150 */
	Uint16 a;
}J150_SYS_INFO;

typedef struct _SYS_STATE_FLAG
{
    ROTATE_DIRECTION 	rotateDirectoin;
    SYSALARM 			alarm;
	SYSWARNING 			warning;
	SYSERRO 			error;
    SYS_RUNNING_STATE 	sysRunningState;
	J150_SYS_STATUS	  	j150SysStatus;
	J150_WORK_MODE		j150WorkMode;
}SYS_STATE_FLAG;

#define CNT_INIT_END (200)

#define SET_SYS_RUNNING_STATE_INIT                      (gSysStateFlag.sysRunningState = SYS_INIT)
#define SET_SYS_RUNNING_STATE_FORWARD_RUN               (gSysStateFlag.sysRunningState = SYS_FORWARD_RUN)
#define SET_SYS_RUNNING_STATE_STOP                      (gSysStateFlag.sysRunningState = SYS_STOP)
#define SET_SYS_RUNNING_STATE_ALARM                     (gSysStateFlag.sysRunningState = SYS_ALARM)

#define IS_SYS_RUNNING_STATE_FORWARD_RUN                (gSysStateFlag.sysRunningState == SYS_FORWARD_RUN)
#define IS_SYS_RUNNING_STATE_ALARM						(gSysStateFlag.sysRunningState == SYS_ALARM)

#define SET_J150_BIT_CMPLT								(gSysStateFlag.j150SysStatus.bit.BIT_CMPLT = 1)
#define CLR_J150_BIT_CMPLT								(gSysStateFlag.j150SysStatus.bit.BIT_CMPLT = 0)
#define SET_J150_POWER_BUS								(gSysStateFlag.j150SysStatus.bit.POWER_BUS = 1)
#define CLR_J150_POWER_BUS								(gSysStateFlag.j150SysStatus.bit.POWER_BUS = 0)
#define SET_J150_FAULT_EXT								(gSysStateFlag.j150SysStatus.bit.FAULT_EXT = 1)
#define CLR_J150_FAULT_EXT								(gSysStateFlag.j150SysStatus.bit.FAULT_EXT = 0)
#define SET_J150_MOTOR_STA								(gSysStateFlag.j150SysStatus.bit.MOTOR_STA = 1)
#define CLR_J150_MOTOR_STA								(gSysStateFlag.j150SysStatus.bit.MOTOR_STA = 0)

#define IS_J150_BIT_CMPLT								(gSysStateFlag.j150SysStatus.bit.BIT_CMPLT == 1)
#define IS_J150_POWER_NOR								(gSysStateFlag.j150SysStatus.bit.POWER_BUS == 1)
#define IS_J150_FAULT_EXT								(gSysStateFlag.j150SysStatus.bit.FAULT_EXT == 1)
#define IS_J150_MOTOR_RUN								(gSysStateFlag.j150SysStatus.bit.MOTOR_STA == 1)

#define SOFTWARE_ALARM_MASK                             BIT0
#define INIT_ALARM_MASK                                 BIT1
#define MOTOR_TEMPERATURE_ALARM_MASK                    BIT2
#define BUS_UNDERVOLTAGE_ALARM_MASK                     BIT3
#define BUS_OVERVOLTAGE_ALARM_MASK                      BIT4
#define BUS_CURRENT_ALARM_MASK                          BIT5
#define HARDWARE_ALARM_MASK                             BIT6
#define POWER_GOOD_VCC5V_ALARM_MASK                     BIT7
#define POWER_GOOD_1V9_ALARM_MASK                       BIT8
#define POWER_GOOD_VCC3V3_ALARM_MASK                    BIT9
#define POWER_GOOD_VDD5V_ALARM_MASK                     BIT10
#define DRIVER_TEMPERATURE_ALARM_MASK                   BIT11
#define BRIDGE_OVER_CURRENT_ALARM_MASK                  BIT12
#define BUS_OVER_CURRENT_ALARM_MASK               	    BIT13
#define BRIDGE_CURRENT_SUM_ALARM_MASK              	    BIT14
#define SW_BUS_OVER_VOLTAGE_ALARM_MASK         		    BIT15
#define CONTROL_VOLTAGE_ALARM_MASK              	    BIT16
#define CONTROL_CURRENT_ALARM_MASK         		    	BIT17
#define MOTOR_OVER_SPEED_ALARM_MASK						BIT18
#define HW_DIGIT_SIGNAL_ALARM_MASK						BIT19
#define HW_DIGITAL_LEVEL_ALARM_MASK						BIT20
#define HW_ANALOG_LEVEL_ALARM_MASK						BIT21
#define HW_CURRENT_ZERO_ALARM_MASK						BIT22
#define SW_PWM_ISR_ALARM_MASK							BIT23

#define IS_SYS_ENABLE_STOP_ROTATE                   	(gSysStateFlag.rotateDirectoin == STOP)
#define SET_SYS_ENABLE_STOP_ROTATE						(gSysStateFlag.rotateDirectoin = STOP)
#define IS_SYS_ENABLE_FORWARD_ROTATE                    (gSysStateFlag.rotateDirectoin == FORWARD)
#define IS_SYS_ENABLE_BACKWARD_ROTATE                   (gSysStateFlag.rotateDirectoin == BACKWARD)
#define IS_SYS_ALARM                                    (gSysStateFlag.alarm.all)
#define IS_SYS_WARNING                                  (gSysStateFlag.warning.all)
#define CLEAR_SYS_ALARM                                 (gSysStateFlag.alarm.all = 0)
#define CLEAR_SYS_WARNING                               (gSysStateFlag.warning.all = 0)
#define CLEAR_SYS_ERROR                                 (gSysStateFlag.error.all = 0)

#define INIT_SYS_RUNNING_STATE                          (gSysStateFlag.sysRunningState = SYS_INIT)
#define INIT_SYS_ROTATE_DIRECTION                       (gSysStateFlag.rotateDirectoin = STOP)
#define INIT_SYS_WORK_MODE								(gSysStateFlag.j150WorkMode = NORMAL)


/*bit0*/
#define SET_SYS_SOFTWARE_ALARM                          (gSysStateFlag.alarm.bit.software = 1)
#define CLEAR_SYS_SOFTWARE_ALARM                        (gSysStateFlag.alarm.bit.software = 0)
#define IS_SYS_SOFTWARE_ALARM                           (gSysStateFlag.alarm.bit.software | SOFTWARE_ALARM_MASK)

/*bit1*/
#define SET_SYS_INIT_ALARM                              (gSysStateFlag.alarm.bit.init = 1)
#define CLEAR_SYS_INIT_ALARM                            (gSysStateFlag.alarm.bit.init = 0)
#define IS_SYS_INIT_ALARM                               (gSysStateFlag.alarm.bit.init | INIT_ALARM_MASK)

/*bit2*/
#define SET_MOTOR_TEMPERATURE_ALARM                     (gSysStateFlag.alarm.bit.motortemp = 1)
#define CLEAR_MOTOR_TEMPERATURE_ALARM                   (gSysStateFlag.alarm.bit.motortemp = 0)
#define IS_MOTOR_TEMPERATURE_ALARM                      (gSysStateFlag.alarm.bit.motortemp | MOTOR_TEMPERATURE_ALARM_MASK)

/*bit3*/
#define SET_SYS_BUS_OVER_VOLTAGE_ALARM                  (gSysStateFlag.alarm.bit.busOV = 1)
#define CLEAR_SYS_BUS_OVER_VOLTAGE_ALARM                (gSysStateFlag.alarm.bit.busOV = 0)
#define IS_SYS_BUS_OVER_VOLTAGE_ALARM                   (gSysStateFlag.alarm.bit.busOV | BUS_OVERVOLTAGE_ALARM_MASK)

/*bit4*/
#define SET_SYS_BUS_UNDER_VOLTAGE_ALARM                 (gSysStateFlag.alarm.bit.busUV = 1)
#define CLEAR_SYS_BUS_UNDER_VOLTAGE_ALARM               (gSysStateFlag.alarm.bit.busUV = 0)
#define IS_SYS_BUS_UNDER_VOLTAGE_ALARM                  (gSysStateFlag.alarm.bit.busUV | BUS_UNDERVOLTAGE_ALARM_MASK)

/*bit5*/
#define SET_SYS_BUS_CURRENT_ALARM                       (gSysStateFlag.alarm.bit.busCurrent = 1)
#define CLEAR_SYS_BUS_CURRENT_ALARM                     (gSysStateFlag.alarm.bit.busCurrent = 0)
#define IS_SYS_BUS_CURRENT_ALARM                        (gSysStateFlag.alarm.bit.busCurrent | BUS_CURRENT_ALARM_MASK)

/*bit6*/
#define SET_SYS_HARDWARE_ALARM                          (gSysStateFlag.alarm.bit.hardware = 1)
#define CLEAR_SYS_HARDWARE_ALARM                        (gSysStateFlag.alarm.bit.hardware = 0)
#define IS_SYS_HARDWARE_ALARM                           (gSysStateFlag.alarm.bit.hardware | HARDWARE_ALARM_MASK)

/*bit7*/
#define SET_SYS_PG_VCC5V_ALARM                          (gSysStateFlag.alarm.bit.pgVcc5V = 1)
#define CLEAR_SYS_PG_VCC5V_ALARM                        (gSysStateFlag.alarm.bit.pgVcc5V = 0)
#define IS_SYS_PG_VCC5V_ALARM                           (gSysStateFlag.alarm.bit.pgVcc5V | POWER_GOOD_VCC5V_ALARM_MASK)

/*bit8*/
#define SET_SYS_PG_1V9_ALARM                            (gSysStateFlag.alarm.bit.pg1v9 = 1)
#define CLEAR_SYS_PG_1V9_ALARM                          (gSysStateFlag.alarm.bit.pg1v9 = 0)
#define IS_SYS_PG_1V9_ALARM                             (gSysStateFlag.alarm.bit.pg1v9 | POWER_GOOD_1V9_ALARM_MASK)

/*bit9*/
#define SET_SYS_PG_VCC3V3_ALARM                         (gSysStateFlag.alarm.bit.pgVcc3V3 = 1)
#define CLEAR_SYS_PG_VCC3V3_ALARM                       (gSysStateFlag.alarm.bit.pgVcc3V3 = 0)
#define IS_SYS_PG_VCC3V3_ALARM                          (gSysStateFlag.alarm.bit.pgVcc3V3 | POWER_GOOD_VCC3V3_ALARM_MASK)

/*bit10*/
#define SET_SYS_PG_VDD5V_ALARM                          (gSysStateFlag.alarm.bit.pgVdd5V = 1)
#define CLEAR_SYS_PG_VDD5V_ALARM                        (gSysStateFlag.alarm.bit.pgVdd5V = 0)
#define IS_SYS_PG_VDD5V_ALARM                           (gSysStateFlag.alarm.bit.pgVdd5V | POWER_GOOD_VDD5V_ALARM_MASK)

/*bit11*/
#define SET_DRIVER_TEMPERATURE_ALARM                    (gSysStateFlag.alarm.bit.drivertemp = 1)
#define CLEAR_DRIVER_TEMPERATURE_ALARM                  (gSysStateFlag.alarm.bit.drivertemp = 0)
#define IS_DRIVER_TEMPERATURE_ALARM                     (gSysStateFlag.alarm.bit.drivertemp | DRIVER_TEMPERATURE_ALARM_MASK)

/*bit12*/
#define SET_BRIDGE_CURRENT_ALARM     	                (gSysStateFlag.alarm.bit.bridgeCurrent = 1)
#define CLEAR_BRIDGE_CURRENT_ALARM       	            (gSysStateFlag.alarm.bit.bridgeCurrent = 0)
#define IS_BRIDGE_CURRENT_ALARM                  	    (gSysStateFlag.alarm.bit.bridgeCurrent | BRIDGE_OVER_CURRENT_ALARM_MASK)

/*bit13*/
#define SET_BUS_CURRENT_ALARM                   		(gSysStateFlag.alarm.bit.swbusCurrent = 1)
#define CLEAR_BUS_CURRENT_ALARM                  		(gSysStateFlag.alarm.bit.swbusCurrent = 0)
#define IS_BUS_CURRENT_ALARM                    		(gSysStateFlag.alarm.bit.swbusCurrent | BUS_OVER_CURRENT_ALARM_MASK)

/*bit14*/
#define SET_BRIDGE_CURRENT_SUM_ALARM                   	(gSysStateFlag.alarm.bit.bridgeSum = 1)
#define CLEAR_BRIDGE_CURRENT_SUM_ALARM             		(gSysStateFlag.alarm.bit.bridgeSum = 0)
#define IS_BRIDGE_CURRENT_SUM_ALARM                     (gSysStateFlag.alarm.bit.bridgeSum | BRIDGE_CURRENT_SUM_ALARM_MASK)

/*bit15*/
#define SET_SW_BUS_OV_ALARM             		      	(gSysStateFlag.alarm.bit.swbusOV = 1)
#define CLEAR_SW_BUS_OV_ALARM           		  		(gSysStateFlag.alarm.bit.swbusOV = 0)
#define IS_SW_BUS_OV_ALARM          		            (gSysStateFlag.alarm.bit.swbusOV | SW_BUS_OVER_VOLTAGE_ALARM_MASK)

/*bit16*/
#define SET_CONTROL_BUS_VOLTAGE_ALARM             		(gSysStateFlag.alarm.bit.ctrlbusVolt = 1)
#define CLEAR_CONTROL_BUS_VOLTAGE_ALARM           		(gSysStateFlag.alarm.bit.ctrlbusVolt = 0)
#define IS_CONTROL_BUS_VOLTAGE_ALARM          		    (gSysStateFlag.alarm.bit.ctrlbusVolt | CONTROL_VOLTAGE_ALARM_MASK)

/*bit17*/
#define SET_CONTROL_BUS_CURRENT_ALARM             		(gSysStateFlag.alarm.bit.ctrlbusCurr = 1)
#define CLEAR_CONTROL_BUS_CURRENT_ALARM           		(gSysStateFlag.alarm.bit.ctrlbusCurr = 0)
#define IS_CONTROL_BUS_CURRENT_ALARM          		    (gSysStateFlag.alarm.bit.ctrlbusCurr | CONTROL_CURRENT_ALARM_MASK)

/*bit18*/
#define SET_MOTOR_OVER_SPEED_ALARM             			(gSysStateFlag.alarm.bit.overspeed = 1)
#define CLEAR_MOTOR_OVER_SPEED_ALARM           			(gSysStateFlag.alarm.bit.overspeed = 0)
#define IS_MOTOR_OVER_SPEED_ALARM          		   	 	(gSysStateFlag.alarm.bit.overspeed | MOTOR_OVER_SPEED_ALARM_MASK)

/*bit19*/
#define SET_HW_DIGIT_SIGNAL_ALARM             			(gSysStateFlag.alarm.bit.hw_digit_sig = 1)
#define CLEAR_HW_DIGIT_SIGNAL_ALARM           			(gSysStateFlag.alarm.bit.hw_digit_sig = 0)
#define IS_HW_DIGIT_SIGNAL_ALARM          		   	 	(gSysStateFlag.alarm.bit.hw_digit_sig | HW_DIGIT_SIGNAL_ALARM_MASK)

/*bit20*/
#define SET_HW_DIGITAL_LEVEL_ALARM             			(gSysStateFlag.alarm.bit.hw_digit_lvl = 1)
#define CLEAR_HW_DIGITAL_LEVEL_ALARM           			(gSysStateFlag.alarm.bit.hw_digit_lvl = 0)
#define IS_HW_DIGITAL_LEVEL_ALARM          		   	 	(gSysStateFlag.alarm.bit.hw_digit_lvl | HW_DIGITAL_LEVEL_ALARM_MASK)

/*bit21*/
#define SET_HW_ANALOG_LEVEL_ALARM             			(gSysStateFlag.alarm.bit.hw_anlg_lvl = 1)
#define CLEAR_HW_ANALOG_LEVEL_ALARM           			(gSysStateFlag.alarm.bit.hw_anlg_lvl = 0)
#define IS_HW_ANALOG_LEVEL_ALARM          		   	 	(gSysStateFlag.alarm.bit.hw_anlg_lvl | HW_ANALOG_LEVEL_ALARM_MASK)

/*bit22*/
#define SET_HW_CURRENT_ZERO_ALARM             			(gSysStateFlag.alarm.bit.hw_I_zero = 1)
#define CLEAR_HW_CURRENT_ZERO_ALARM           			(gSysStateFlag.alarm.bit.hw_I_zero = 0)
#define IS_HW_CURRENT_ZERO_ALARM          		   	 	(gSysStateFlag.alarm.bit.hw_I_zero | HW_CURRENT_ZERO_ALARM_MASK)

/*bit23*/
#define SET_SW_PWM_ISR_ALARM             				(gSysStateFlag.alarm.bit.sw_pwm_alarm = 1)
#define CLEAR_SW_PWM_ISR_ALARM           				(gSysStateFlag.alarm.bit.sw_pwm_alarm = 0)
#define IS_SW_PWM_ISR_ALARM          		   	 		(gSysStateFlag.alarm.bit.sw_pwm_alarm | SW_PWM_ISR_ALARM_MASK)


#define SET_MOTOR_TEMPERATURE_WARNING                   (gSysStateFlag.warning.bit.motortemp = 1)
#define CLEAR_MOTOR_TEMPERATURE_WARNING                 (gSysStateFlag.warning.bit.motortemp = 0)
#define IS_MOTOR_TEMPERATURE_WARNING                    (gSysStateFlag.warning.bit.motortemp | MOTOR_TEMPERATURE_WARNING_MASK)

#define SET_DRIVER_TEMPERATURE_WARNING                  (gSysStateFlag.warning.bit.drivertemp = 1)
#define CLEAR_DRIVERR_TEMPERATURE_WARNING               (gSysStateFlag.warning.bit.drivertemp = 0)
#define IS_DRIVER_TEMPERATURE_WARNING                   (gSysStateFlag.warning.bit.drivertemp | DRIVER_TEMPERATURE_WARNING_MASK)

#define SET_SYS_MEMORY_MOLLOC_ERROR                     (gSysStateFlag.error.bit.memoryFull = 1)
#define CLEAR_SYS_MEMORY_MOLLOC_ERROR                   (gSysStateFlag.error.bit.memoryFull = 0)
#define IS_SYS_MEMORY_MOLLOC_ERROR                      (gSysStateFlag.error.bit.memoryFull | BIT6)

#define SET_SYS_RX_QUEUE_FULL_ERROR                     (gSysStateFlag.error.bit.rxQFull = 1)
#define CLEAR_SYS_RX_QUEUE_FULL_ERROR                   (gSysStateFlag.error.bit.rxQFull = 0)
#define IS_SYS_RX_QUEUE_FULL_ERROR                      (gSysStateFlag.error.bit.rxQFull | BIT7)

#define SET_SYS_TX_QUEUE_FULL_ERROR                     (gSysStateFlag.error.bit.txQFull = 1)
#define CLEAR_SYS_TX_QUEUE_FULL_ERROR                   (gSysStateFlag.error.bit.txQFull = 0)
#define IS_SYS_TX_QUEUE_FULL_ERROR                      (gSysStateFlag.error.bit.txQFull | BIT8)

#define SYS_STATE_MACHINE								(*Sys_hlstPtr)()

extern void (*Sys_hlstPtr)(void);
void Init_Sys_State_Service(void);
extern SYS_STATE_FLAG gSysStateFlag;
extern Uint16 gSysVersionNum;
void checkOutputGPIOs (void);
void checkInputGPIOs (void);
void period_BIT(void);
void powerOn_BIT(void);
#endif
