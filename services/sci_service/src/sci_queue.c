#include "sci_queue.h"


int SciRxEnQueue(int e, SCIRXQUE *RS422RxQue)
{
	if((RS422RxQue->rear + 1) % (RS422RxQue->bufferLen) == RS422RxQue->front)
	{
		SET_SYS_RX_QUEUE_FULL_ERROR;
		RS422RxQue->front = (RS422RxQue->front + 1) % (RS422RxQue->bufferLen);
	}

	RS422RxQue->buffer[RS422RxQue->rear] = e;
	RS422RxQue->rear = (RS422RxQue->rear + 1) % (RS422RxQue->bufferLen);
	return 1;
}

int SciRxDeQueue(SCIRXQUE *RS422RxQue)
{
	if(RS422RxQue->front == RS422RxQue->rear)
	{
		return 0;
	}

	RS422RxQue->front = (RS422RxQue->front + 1) % (RS422RxQue->bufferLen);
	return 1;
}

int GetSciRxQueLength(SCIRXQUE *RS422RxQue)
{
	int length;
	length = (RS422RxQue->rear - RS422RxQue->front + (RS422RxQue->bufferLen)) % (RS422RxQue->bufferLen);
	return length;
}

int SciTxEnQueue(char e, SCITXQUE *RS422TxQue)
{
	if((RS422TxQue->rear + 1) % (RS422TxQue->bufferLen) == RS422TxQue->front)
	{
		SET_SYS_TX_QUEUE_FULL_ERROR;
		RS422TxQue->front = (RS422TxQue->front + 1) % (RS422TxQue->bufferLen);
		return 0;
	}
	RS422TxQue->buffer[RS422TxQue->rear] = e;
	RS422TxQue->rear = (RS422TxQue->rear + 1) % (RS422TxQue->bufferLen);
	return 1;
}
int SciTxDeQueue(SCITXQUE *RS422TxQue)
{
	if(RS422TxQue->front == RS422TxQue->rear)
	{
		return 0;
	}

	RS422TxQue->front = (RS422TxQue->front + 1) % (RS422TxQue->bufferLen);
	return 1;
}

int GetSciTxQueLength(SCITXQUE *RS422TxQue)
{
	int length;
	length = (RS422TxQue->rear - RS422TxQue->front + (RS422TxQue->bufferLen)) % (RS422TxQue->bufferLen);
	return length;
}
