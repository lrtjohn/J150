#ifndef ARINC_429_SERVICE_H_
#define ARINC_429_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod_defs.h"

typedef struct{
	Uint16 LowByte : 8;
	Uint16 HighByte	: 8;
}ARINCVAR16BIT;

typedef struct{
	Uint16 RxDataRate : 1;
	Uint16 ArincClkSrcSel : 1;
	Uint16 EnlLalRecgn : 1;
    Uint16 TxParityChkEnl : 1;
	Uint16 RxParityChkEnl : 1;
	Uint16 SelfTest : 1;
	Uint16 RxDeocder : 1;
	Uint16 RFU1 : 1;
	Uint16 RFU2 : 1;
	Uint16 TxParitySel : 1;
	Uint16 TxDataRate : 1;
	Uint16 ArincLblBitOrder : 1;
	Uint16 DisableLineDriver : 1;
	Uint16 TxEnlMode : 1;
	Uint16 TxFlagDefination : 1;
	Uint16 RxFlagDefination : 1;
}ARINC429_CTL_REG_BIT16;


typedef struct{
	Uint16 RxFifoEmpty : 1;
	Uint16 RxFifoHalFull : 1;
	Uint16 RxFifoFull : 1;
    Uint16 TxFifoEmpty : 1;
	Uint16 TxFifoHalFull : 1;
	Uint16 TxFifoFull : 1;
	Uint16 RFU0 : 1;
	Uint16 RFU1 : 1;
	Uint16 RFU2 : 1;
	Uint16 RFU3 : 1;
	Uint16 RFU4 : 1;
	Uint16 RFU5 : 1;
	Uint16 RFU6 : 1;
	Uint16 RFU7 : 1;
	Uint16 RFU8 : 1;
	Uint16 RFU9 : 1;
}ARINC429_STATUS_REG_BIT8;

typedef union
{
    Uint16 all;
    ARINC429_CTL_REG_BIT16 regVale;
	ARINCVAR16BIT HighLowByte;
}ARINC429_CTL_REG;

typedef union
{
    Uint16 all;
    ARINC429_STATUS_REG_BIT8 regVale;
	ARINCVAR16BIT HighLowByte;
}ARINC429_STATUS_REG;


typedef struct
{
	Uint16 arinc429RegStatus;
	Uint16 arinc429CtlReg;
}ARINC429_PARA;


#define ArincRxFifoEmptyMask				BIT0
#define ArincRxFifoHalFullMask				BIT1
#define ArincRxFifoFullMask					BIT2
#define ArincTxFifoEmptyMask				BIT3
#define ArincTxFifoHalFullMask				BIT4
#define ArincTxFifoFullMask					BIT5
#define ArincArincRxFifoEmptyMask			BIT6

#define IsArincRxFifoEmpty(a)					(a & ArincRxFifoEmptyMask)
#define IsArincRxFifoHalFull(a)					(a & ArincRxFifoHalFullMask)
#define IsArincRxFifoFull(a)					(a & ArincRxFifoFullMask)
#define IsArincTxFifoEmpty(a)					(a & ArincTxFifoEmptyMask)
#define IsArincTxFifoHalFull(a)					(a & ArincTxFifoHalFullMask)			
#define IsArincTxFifoFull(a)					(a & ArincTxFifoFullMask)	
#define IsArincArincRxFifoEmptyMask(a)			(a & ArincArincRxFifoEmptyMask)


#define ArincRxDataRateMask						BIT0			
#define ArincArincClkSrcSelMask					BIT1
#define ArincEnlLalRecgnMask					BIT2		
#define ArincTxParityChkEnlMask					BIT3	
#define ArincRxParityChkEnlMask					BIT4
#define ArincSelfTestMask						BIT5	
#define ArincRxDeocderMask						BIT6
#define ArincRFU1Mask							BIT7		
#define ArincRFU2Mask							BIT8		
#define ArincTxParitySelMask					BIT9
#define ArincTxDataRateMask						BIT10
#define ArincArincLblBitOrderMask				BIT11	
#define ArincDisableLineDriverMask				BIT12	
#define ArincTxEnlModeMask						BIT13
#define ArincTxFlagDefinationMask				BIT14
#define ArincRxFlagDefinationMask				BIT15	



#define IsArincRxDataRate(a)						(a & ArincRxDataRateMask)					
#define IsArincArincClkSrcSel(a)					(a & ArincArincClkSrcSelMask)
#define IsArincEnlLalRecgn(a)						(a & ArincEnlLalRecgnMask)
#define IsArincTxParityChkEnl(a)					(a & ArincTxParityChkEnlMask)
#define IsArincRxParityChkEnl(a)					(a & ArincRxParityChkEnlMask)
#define IsArincSelfTest(a)							(a & ArincSelfTestMask)
#define IsArincRxDeocder(a)							(a & ArincRxDeocderMask)
#define IsArincRFU1(a)								(a & ArincRFU1Mask)
#define IsArincRFU2(a)								(a & ArincRFU2Mask)
#define IsArincTxParitySel(a)						(a & ArincTxParitySelMask)
#define IsArincTxDataRate(a)						(a & ArincTxDataRateMask)
#define IsArincArincLblBitOrder(a)					(a & ArincArincLblBitOrderMask)
#define IsArincDisableLineDriver(a)					(a & ArincDisableLineDriverMask)
#define IsArincTxEnlMode(a)							(a & ArincTxEnlModeMask)
#define IsArincTxFlagDefination(a)					(a & ArincTxFlagDefinationMask)
#define IsArincRxFlagDefination(a)					(a & ArincRxFlagDefinationMask)


#define EnableArincLableRecognition(a)				(a | ArincEnlLalRecgnMask)


#define Assert_CS_DELAY    		(20)
#define Deassert_CS_DELAY    	(20)
#define Assert_CS_Pin()\
						{\
							GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;\
							int i;\
							for(i = 0; i < Assert_CS_DELAY; ++i)\
							{\
								asm (" NOP");\
    						}\
						}

#define Deassert_CS_Pin()\
						{\
							GpioDataRegs.GPBSET.bit.GPIO61 = 1;\
							int i;\
							for(i = 0; i < Deassert_CS_DELAY; ++i)\
							{\
								asm (" NOP");\
    						}\
						}


#define Read_ARINC_TFLAG_PIN_STATUS		GpioDataRegs.GPBDATA.bit.GPIO59
#define Read_ARINC_RFLAG_PIN_STATUS		GpioDataRegs.GPBDATA.bit.GPIO35


#define Arinc429_MR_ASSERT              (GpioDataRegs.GPBSET.bit.GPIO60 = 1)
#define Arinc429_MR_DEASSERT            (GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1)

Uint32 	Arinc429_SetCtlReg(ARINC429_CTL_REG ctlRegVal);
Uint16 	Arinc429_ReadStatusReg(void);
Uint16 	Arinc429_ReadCtlReg(void);
Uint32	Arinc429_ReadRxFIFO_ONE_WORD(void);
Uint32  Arinc429_WriteTxFIFO_ONE_WORD(Uint32 data);
void 	Arinc429_MasterReset(void);
void 	Arinc429_InitCtlReg(void);
void 	Init_Arinc429_Service(void);
#endif

