#include "sci_service.h"
#include "gpio_service.h"

void Sci_B_Receive(SCIRXQUE* RS422RxQue)
{
	int16 data;

	while(ScibRegs.SCIFFRX.bit.RXFFST != 0)
	{// rs422 rx fifo is not empty
		data = ScibRegs.SCIRXBUF.all;
		if(SciRxEnQueue(data, RS422RxQue) == 0)
		{
			// gSysState.alarm.bit.rs422RxQFull = 1;
		}
	}
}

void DisableScibTxInterrupt(void)
{
	ScibRegs.SCIFFTX.bit.TXFFIENA = 0;
}

void ScibTxByte(Uint16 t)
{
	ScibRegs.SCITXBUF = t;
}

void SCI_B_Transmit(SCITXQUE* RS422TxQue)
{

	if(RS422TxQue->front == RS422TxQue->rear)
	{
		DisableScibTxInterrupt();//disable the tx interrupt when tx fifo empty
		return;
	}
	while((ScibRegs.SCIFFTX.bit.TXFFST != 16))
	{
		if(GetSciTxQueLength(RS422TxQue) == 0)
		{
			return;
		}

		ScibTxByte(RS422TxQue->buffer[RS422TxQue->front]);//printf by Scic

		if(SciTxDeQueue(RS422TxQue) == 0)
		{
			DisableScibTxInterrupt();
			return;
		}
	}
}

void ClearScibRxOverFlow(void)
{
	if (ScibRegs.SCIFFRX.bit.RXFFOVF == 1)
	{
		// printf(">>>>>>scib rx fifo over flow\r\n");
		ScibRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
		if (ScibRegs.SCIFFRX.bit.RXFFOVF == 0)
		{
//			printf(">>scib clear fifo over flow flag\r\n");
		}
	}
}

void CheckScibRxError(void){
	if(ScibRegs.SCIRXST.bit.RXERROR == 1){
		ScibRegs.SCICTL1.bit.SWRESET = 0;
//		DELAY_NOPS(5);
//		ScibRegs.SCICTL1.bit.SWRESET = 1;
	}
	else{
		ScibRegs.SCICTL1.bit.SWRESET = 1;
	}
}

void EnableScibTxInterrupt(void)
{
	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScibRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void CheckEnableScibTx(SCITXQUE* RS422TxQue)
{
	if(RS422TxQue->front != RS422TxQue->rear
		&& ScibRegs.SCIFFTX.bit.TXFFST == 0)
	{
		 EnableScibTxInterrupt();
	}
}
