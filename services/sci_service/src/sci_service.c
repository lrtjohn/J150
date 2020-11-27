#include "sci_service.h"
#include "gpio_service.h"

void Sci_A_Receive(SCIRXQUE* RS422RxQue)
{
	int16 data;

	while(SciaRegs.SCIFFRX.bit.RXFFST != 0)
	{// rs422 rx fifo is not empty
		data = SciaRegs.SCIRXBUF.all;
		if(SciRxEnQueue(data, RS422RxQue) == 0)
		{
			// gSysState.alarm.bit.rs422RxQFull = 1;
		}
	}
}

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

void Sci_C_Receive(SCIRXQUE* RS422RxQue)
{
	int16 data;

	while(ScicRegs.SCIFFRX.bit.RXFFST != 0)
	{// rs422 rx fifo is not empty
		data = ScicRegs.SCIRXBUF.all;
		if(SciRxEnQueue(data, RS422RxQue) == 0)
		{
			// gSysState.alarm.bit.rs422RxQFull = 1;
		}
	}
}


void DisableSciaTxInterrupt(void)
{
	SciaRegs.SCIFFTX.bit.TXFFIENA = 0;
}
void DisableScibTxInterrupt(void)
{
	ScibRegs.SCIFFTX.bit.TXFFIENA = 0;
}
void DisableScicTxInterrupt(void)
{
	ScicRegs.SCIFFTX.bit.TXFFIENA = 0;
}
void SciaTxByte(Uint16 t)
{
	SciaRegs.SCITXBUF = t;
}
void ScibTxByte(Uint16 t)
{
	ScibRegs.SCITXBUF = t;
}
void ScicTxByte(Uint16 t)
{
	ScicRegs.SCITXBUF = t;
}
void SCI_A_Transmit(SCITXQUE* RS422TxQue)
{

	if(RS422TxQue->front == RS422TxQue->rear)
	{
		DisableSciaTxInterrupt();//disable the tx interrupt when tx fifo empty
		return;
	}
	while((SciaRegs.SCIFFTX.bit.TXFFST != 16))
	{
		if(GetSciTxQueLength(RS422TxQue) == 0)
		{
			return;
		}
		SciaTxByte(RS422TxQue->buffer[RS422TxQue->front]);//printf by Scic

		if(SciTxDeQueue(RS422TxQue) == 0)
		{
			DisableSciaTxInterrupt();
			return;
		}
	}
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

void SCI_C_Transmit(SCITXQUE* RS422TxQue)
{

	if(RS422TxQue->front == RS422TxQue->rear)
	{
		DisableScicTxInterrupt();//disable the tx interrupt when tx fifo empty
		return;
	}
	while((ScicRegs.SCIFFTX.bit.TXFFST != 16))
	{
		if(GetSciTxQueLength(RS422TxQue) == 0)
		{
			return;
		}
		ScicTxByte(RS422TxQue->buffer[RS422TxQue->front]);//printf by Scic

		if(SciTxDeQueue(RS422TxQue) == 0)
		{
			DisableScicTxInterrupt();
			return;
		}
	}
}


void ClearSciaRxOverFlow(void) 
{
	if (SciaRegs.SCIFFRX.bit.RXFFOVF == 1)
	{
		// printf(">>>>>>scib rx fifo over flow\r\n");
		SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
		if (SciaRegs.SCIFFRX.bit.RXFFOVF == 0)
		{
//			printf(">>scib clear fifo over flow flag\r\n");
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

void ClearScicRxOverFlow(void)
{
	if (ScicRegs.SCIFFRX.bit.RXFFOVF == 1)
	{
		// printf(">>>>>>scib rx fifo over flow\r\n");
		ScicRegs.SCIFFRX.bit.RXFFOVRCLR = 1;
		ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
		if (ScicRegs.SCIFFRX.bit.RXFFOVF == 0)
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

void EnableSciaTxInterrupt(void)
{
	SciaRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	SciaRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void EnableScibTxInterrupt(void)
{
	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScibRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void EnableScicTxInterrupt(void)
{
	ScicRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScicRegs.SCIFFTX.bit.TXFFIENA = 1;
}

void CheckEnableSciaTx(SCITXQUE* RS422TxQue)
{
	if(RS422TxQue->front != RS422TxQue->rear
		&& SciaRegs.SCIFFTX.bit.TXFFST == 0)
	{
		 EnableSciaTxInterrupt();
	}
}

void CheckEnableScibTx(SCITXQUE* RS422TxQue)
{
	if(RS422TxQue->front != RS422TxQue->rear
		&& ScibRegs.SCIFFTX.bit.TXFFST == 0)
	{
		 EnableScibTxInterrupt();
	}
}


void CheckEnableScicTx(SCITXQUE* RS422TxQue)
{
	if(RS422TxQue->front != RS422TxQue->rear
		&& ScicRegs.SCIFFTX.bit.TXFFST == 0)
	{

		 EnableScicTxInterrupt();
	}
}




