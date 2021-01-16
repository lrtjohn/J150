#include "sci_protocal.h"
//#include <stdio.h>
#include <string.h>
SCIRXQUE* gScibRxQue = NULL;
SCITXQUE* gScibTxQue = NULL;
char rs422rxPack[100] = {0};

#if(SYS_DEBUG == INCLUDE_FEATURE)
int gscitest = 0;
#endif

static void DebugTest(VAR16 a, int b, int c) {
#if(SYS_DEBUG == INCLUDE_FEATURE)
	    gscitest++;
#endif
}
const functionMsgCodeUnpack SDB_MsgFuncTbl[] = 
{
    DebugTest,
    0,
    0,
    0
};
int SciRxCalCrc(int crc, const char *buf, int len)
{
	int x;
	int i;

	for(i = 0; i < len; ++i){
		x = ((crc >> 8) ^ buf[i]) & 0xff;
		x ^= x >> 4;
		crc = (crc << 8) ^ (x  << 12) ^ (x << 5) ^ x;
		crc &= 0xffff;
	}
	return crc;
}

int FindRxPacketHead(SCIRXQUE *RS422RxQue)
{

	char head1;
	char head2;

	while(1)
	{
		head1 = RS422RxQue->buffer[RS422RxQue->front];
		head2 = RS422RxQue->buffer[(RS422RxQue->front + 1) % (RS422RxQue->bufferLen)];

		if(head1 == HEAD1 && head2 == HEAD2)
		{
			return SUCCESS;
		}

		if(SciRxDeQueue(RS422RxQue) == 0)
		{
			return FAIL;
		}
	}
}

int FindRxPacketTail(int len, SCIRXQUE *RS422RxQue)
{
	char tail1;
	char tail2;

	tail1 = RS422RxQue->buffer[(RS422RxQue->front + len - 1) % (RS422RxQue->bufferLen)];
	tail2 = RS422RxQue->buffer[(RS422RxQue->front + len - 2) % (RS422RxQue->bufferLen)];

	if(tail1 == TAIL1 && tail2 == TAIL2)
	{
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

int CheckRxPacketLength(SCIRXQUE *RS422RxQue)
{

	if((RS422RxQue->buffer[(RS422RxQue->front + 2) % (RS422RxQue->bufferLen)] * UNIT_LEN + EXTRA_LEN) <= GetSciRxQueLength(RS422RxQue))
	{
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

void SaveRxPacketProfile(int len, SCIRXQUE *RS422RxQue)
{
	int i;

	for(i = 0; i < len; ++i)
	{
		rs422rxPack[i] = RS422RxQue->buffer[(RS422RxQue->front + i) % (RS422RxQue->bufferLen)];
	}
}

void UnpackRxProfile(int len)
{
	int i;
	int msgCode;
	VAR16 var16;

	for(i = 0; i < len; ++i){

		msgCode = rs422rxPack[OFFSET + UNIT_LEN * i];
		var16.datahl.h = rs422rxPack[OFFSET + UNIT_LEN*i + 1];
		var16.datahl.l = rs422rxPack[OFFSET + UNIT_LEN*i + 2];
		//var16.value = var16.datahl.l + (var16.datahl.h << 8);

		if(msgCode < (sizeof(SDB_MsgFuncTbl) / sizeof(SDB_MsgFuncTbl[0])))
		{
			//printf("msgCode = %d\r\n",msgCode);
			if(SDB_MsgFuncTbl[msgCode])
			{
				SDB_MsgFuncTbl[msgCode](var16, 0, 0);
			}
		}
		else
		{
			//printf("unpack msg code is out of range\r\n");
		}
	}
}

void UpdateRxQueueHeadPos(int len, SCIRXQUE *RS422RxQue)
{
	RS422RxQue->front = (RS422RxQue->front + len) % (RS422RxQue->bufferLen);
}

//////////////////////////////////////////////SCI RX END, SCI TX BEGIN

int SciTxCalCrc(int crc, const char *buf, int len)
{
	int x;
	int i;

	for(i = 0; i < len; ++i)
	{
		x = ((crc >> 8) ^ buf[i]) & 0xff;
		x ^= x >> 4;
		crc = (crc << 8) ^ (x  << 12) ^ (x << 5) ^ x;
		crc &= 0xffff;
	}
	return crc;
}

#define S 0

int gmalloc = 0;
void Init_Sci_Protocol(void)
{
	if(gScibRxQue == NULL)
	{
		gScibRxQue = (SCIRXQUE*)malloc(sizeof(SCIRXQUE));
		if(gScibRxQue == NULL)
		{
			//TODO generate alarm
			gmalloc = gmalloc | 0x01;
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		gScibRxQue->front = 0;
		gScibRxQue->rear = 0;
		gScibRxQue->bufferLen = 200;
		gScibRxQue->buffer = (Uint16*)malloc(sizeof(Uint16) * gScibRxQue->bufferLen);
		if(gScibRxQue->buffer == NULL)
		{
			gmalloc = gmalloc | 0x02;
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		memset(gScibRxQue->buffer, 0 , sizeof(gScibRxQue->buffer));
	}

	if(gScibTxQue == NULL)
	{
		gScibTxQue = (SCITXQUE*)malloc(sizeof(SCITXQUE));
		if(gScibTxQue == NULL)
		{
			gmalloc = gmalloc | 0x04;
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		gScibTxQue->front = 0;
		gScibTxQue->rear = 0;
		gScibTxQue->bufferLen = 200;
		gScibTxQue->buffer = (Uint16*)malloc(sizeof(Uint16) * gScibTxQue->bufferLen);
		if(gScibTxQue->buffer == NULL)
		{
			gmalloc = gmalloc | 0x08;
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
		memset(gScibTxQue->buffer, 0 , sizeof(gScibTxQue->buffer));
	}
}

int PF_GetRingBufferDataSize(PF_RING_BUFFER *ringBuffer)
{
	int length;
	length = (ringBuffer->rear - ringBuffer->front + (ringBuffer->bufferLen)) % (ringBuffer->bufferLen);
	return length;
}

void PF_UnpackRxProfile(Uint16* profilePtr, int len)
{
	int i;
	int msgCode;
	VAR16 var16;

	for(i = 0; i < len; ++i){

		msgCode = profilePtr[OFFSET + UNIT_LEN * i];
		var16.datahl.h = profilePtr[OFFSET + UNIT_LEN * i + 1];
		var16.datahl.l = profilePtr[OFFSET + UNIT_LEN * i + 2];
		//var16.value = var16.datahl.l + (var16.datahl.h << 8);

		if(msgCode < (sizeof(SDB_MsgFuncTbl) / sizeof(SDB_MsgFuncTbl[0])))
		{
			//printf("msgCode = %d\r\n",msgCode);
			if(SDB_MsgFuncTbl[msgCode])
			{
				SDB_MsgFuncTbl[msgCode](var16, 0, 0);
			}
		}
		else
		{
			//printf("unpack msg code is out of range\r\n");
		}
	}
}

void PF_UpdateRxQueueHeadPos(int len, PF_RING_BUFFER *ringBuffer)
{
	ringBuffer->front = (ringBuffer->front + len) % (ringBuffer->bufferLen);
}

int PF_CalCrc(int crc, const Uint16 *buf, int len)
{
	int x;
	int i;

	for(i = 0; i < len; ++i){
		x = ((crc >> 8) ^ buf[i]) & 0xff;
		x ^= x >> 4;
		crc = (crc << 8) ^ (x  << 12) ^ (x << 5) ^ x;
		crc &= 0xffff;
	}
	return crc;
}
