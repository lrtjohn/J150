#include "sci_protocal.h"
//#include <stdio.h>
#include <string.h>
SCIRXQUE* gScibRxQue = NULL;
SCITXQUE* gScibTxQue = NULL;
SCITXVAR* gSciTxVar = NULL;
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

void ProcessSciRxPacket(SCIRXQUE *RS422RxQue)
{
	int length;
	while(GetSciRxQueLength(RS422RxQue) > EXTRA_LEN)
	{
		if(FindRxPacketHead(RS422RxQue) == FAIL)
		{
			//printf("find head failed\r\n");
			return;
		}
		else
		{
			//printf("find head succeed\r\n");
		}

		if(CheckRxPacketLength(RS422RxQue) == FAIL)
		{
			return;
		}
		else
		{
			//printf("Check data length succeed, begin to check tail\r\n");
		}

		length = RS422RxQue->buffer[(RS422RxQue->front + 2) % (RS422RxQue->bufferLen)] * UNIT_LEN + EXTRA_LEN;

		if(FindRxPacketTail(length,RS422RxQue) == FAIL)
		{
			//printf("find tail failed\r\n");
			if(SciRxDeQueue(RS422RxQue) == 0)
			{
				//printf("RS422 rx queue is empty\r\n");
			}
			return;
		}
		else
		{
			//printf("find tail succeed\r\n");
		}

		SaveRxPacketProfile(length,RS422RxQue);

		if(SciRxCalCrc(0, rs422rxPack + OFFSET, length - EXTRA_LEN + 2) != 0)
		{
			if(SciRxDeQueue(RS422RxQue) == 0)
			{
				//printf("RS422 rx queue is empty\r\n");
			}
			//printf("CRC check failed\r\n");
			return;
		}
		else
		{
			//printf("CRC check succeed\r\n");
		}

		UnpackRxProfile(RS422RxQue->buffer[(RS422RxQue->front + 2) % (RS422RxQue->bufferLen)]);

		UpdateRxQueueHeadPos(length, RS422RxQue);
	}
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
#define TOTAL_TX_VAR (8)
#define S 0
Uint16 gRx422TxEnableFlag[TOTAL_TX_VAR] = {0};
void UpdateSciTxEnableFlag(SCITXVAR* sciTxVar, int len)
{
	int i;
	for (i = 0; i < len; ++i)
	{
		sciTxVar[i].isTx = gRx422TxEnableFlag[i];
	}
}


 void PackSciTxPacket(SCITXQUE *RS422TxQue, SCITXVAR* sciTxVar)
 {
 	int i;
 	char crcl;
 	char crch;
 	static unsigned char count = 0;
 	static int crc = 0;
 	char tmp[3] = {0};
 	int lenPosition = 0;
 	Uint16 total =0;
	static int times = 0;

	++times;
	if(times < 1000)
	{
		return;
	}
	times = 0;

 	if(count == 0)
	{
 		if(SciTxEnQueue(0x5a,RS422TxQue) == 0)
		 {
 			return;
 		}
 		if(SciTxEnQueue(0x5a,RS422TxQue) == 0)
		{
 			return;
 		}
 		lenPosition = RS422TxQue->rear;
 		if(SciTxEnQueue(0x05,RS422TxQue) == 0)
		{
 			return;
 		}
 		if(SciTxEnQueue(0xff,RS422TxQue) == 0)
		{
 			return;
 		}
 		if(SciTxEnQueue(0xff,RS422TxQue) == 0)
		{
 			return;
 		}
 		UpdateSciTxEnableFlag(sciTxVar,TOTAL_TX_VAR);
 	}

 	for(i = 0; i < TOTAL_TX_VAR; ++i)
	{
 		if(sciTxVar[i].isTx)
		{
 			++total;

 			sciTxVar[i].updateValue(0,0,0);
 			tmp[0] = sciTxVar[i].index;
 			tmp[1] = sciTxVar[i].value >> 8;
 			tmp[2] = sciTxVar[i].value;
 			if(SciTxEnQueue(sciTxVar[i].index, RS422TxQue) == 0)
			{
 				return;
 			}
 			if(SciTxEnQueue((sciTxVar[i].value >> 8), RS422TxQue) == 0)
			{
 				return;
 			}
 			if(SciTxEnQueue(sciTxVar[i].value, RS422TxQue) == 0)
			{
 				return;
 			}
 			crc = SciTxCalCrc(crc, tmp, 3);
 		}
 	}

 	if(count == 0)
	{
 		RS422TxQue->buffer[lenPosition] = total * (S + 1);//timer0 interrupt isr can not be interrupted by TX, so we can set length value here
 	}

 	++count;

 	if(count > S)
	{

 		crcl = (char)crc;
 		crch = (char)(crc >> 8);
 		crc = 0;
 		count = 0;
 		if(SciTxEnQueue(crch, RS422TxQue) == 0)
		{
 			return;
 		}
 		if(SciTxEnQueue(crcl, RS422TxQue) == 0)
		{
 			return;
 		}
 		if(SciTxEnQueue(0xa5, RS422TxQue) == 0)
		{
 			return;
 		}
 		if(SciTxEnQueue(0xa5, RS422TxQue) == 0)
		{
 			return;
 		}
 	}
 }



void GetTorqueCurve(int a, int b, int c)
{
#if(SYS_DEBUG == INCLUDE_FEATURE)
	    gSciTxVar[0].value = 10;
#endif
}
void GetMotorSpeedCurve(int a, int b, int c)
{


}
void GetDisplacementCurve(int a, int b, int c)
{

}
void GetMotorCurrentCurve(int a, int b, int c)
{
	
}
void GetDynamoVoltageCurve(int a, int b, int c)
{
	
}
void GetDynamoCurrentCurve(int a, int b, int c)
{
	
}
void GetTemperatureCurve(int a, int b, int c)
{

}
void GetMotorAccelCurve(int a, int b, int c)
{
	
}

PF_RX_PACKET_HEAD* gRxPacketHead = NULL;
PF_RX_PACKET_TAIL* gRxPacketTail = NULL;
PF_RX_PACKET_INFO* gRxPacketInfo = NULL;
Uint16 calRxPacketTotalLen(Uint16 a)
{
    Uint16 ret;
    ret = a * 3  + 9;

	return ret;
}
int gmalloc = 0;
void Init_Sci_Protocol(void)
{

	int index;

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

	if(gSciTxVar == NULL)
	{
		gSciTxVar = (SCITXVAR*)malloc(sizeof(SCITXVAR) * 8);
		if(gSciTxVar == NULL)
		{
			//TODO generate alarm
			gmalloc = gmalloc | 0x10;
			SET_SYS_MEMORY_MOLLOC_ERROR;
			return;
		}
	}

	memset(gSciTxVar, 0, sizeof(gSciTxVar));

	for (index = 0; index < 8; ++index)
	{
		gSciTxVar[index].isTx = 0;
		gSciTxVar[index].index = index;
		gRx422TxEnableFlag[index] = 0;
	}
#if(SYS_DEBUG == INCLUDE_FEATURE)
	gRx422TxEnableFlag[0] = 1;
#endif
	gSciTxVar[0].updateValue = GetTorqueCurve;
	gSciTxVar[1].updateValue = GetMotorSpeedCurve;
	gSciTxVar[2].updateValue = GetDisplacementCurve;
	gSciTxVar[3].updateValue = GetMotorCurrentCurve;
	gSciTxVar[4].updateValue = GetDynamoVoltageCurve;
	gSciTxVar[5].updateValue = GetDynamoCurrentCurve;
	gSciTxVar[6].updateValue = GetTemperatureCurve;
	gSciTxVar[7].updateValue = GetMotorAccelCurve;


	gRxPacketHead = (PF_RX_PACKET_HEAD*)malloc(sizeof(PF_RX_PACKET_HEAD));
	if(gRxPacketHead == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0020;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return;
	}
	gRxPacketHead->headLen = 2;
	gRxPacketHead->head = (Uint16*)malloc(sizeof(Uint16) * 2);
	if(gRxPacketHead->head == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0040;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return;
	}
	gRxPacketHead->head[0] = 0x5a;
	gRxPacketHead->head[1] = 0x5a;

	gRxPacketTail = (PF_RX_PACKET_TAIL*)malloc(sizeof(PF_RX_PACKET_TAIL));
	if(gRxPacketTail == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0080;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return;
	}
	gRxPacketTail->tailLen = 2;
	gRxPacketTail->tail = (Uint16*)malloc(sizeof(Uint16) * 2);
	if(gRxPacketTail->tail == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0100;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return;
	}
	gRxPacketTail->tail[0] = 0xa5;
	gRxPacketTail->tail[1] = 0xa5;


	gRxPacketInfo = (PF_RX_PACKET_INFO*)malloc(sizeof(PF_RX_PACKET_INFO));
	if(gRxPacketInfo == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0100;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return;
	}
	gRxPacketInfo->lenPos = 2;
	gRxPacketInfo->minLen = 9;
	gRxPacketInfo->extraLen = 9;
	gRxPacketInfo->profileStartPos = 5;
	gRxPacketInfo->totallLen = 0;

	gRxPacketInfo->updateTotalLen = calRxPacketTotalLen;
}

int PF_FindRxPacketHead(PF_RING_BUFFER *ringBuffer)
{
    int i;
    int flag = SUCCESS;
	while(1)
	{
        for(i = 0; i < gRxPacketHead->headLen; ++i)
        {
            if(gRxPacketHead->head[i] != ringBuffer->buffer[(ringBuffer->front + 1) % (ringBuffer->bufferLen)])
            {
                flag = 0;
            }
        }

        if(flag == SUCCESS)
        {
            return SUCCESS;
        }

		if(SciRxDeQueue(ringBuffer) == 0)
		{
			return FAIL;
		}
	}
}


int PF_FindRxPacketTail(int len, PF_RING_BUFFER *ringBuffer)
{
	int i;
	int flag = SUCCESS;

	for(i = 0; i < gRxPacketTail->tailLen; ++i)
	{
		if(gRxPacketTail->tail[i] != ringBuffer->buffer[(ringBuffer->front + len - 1 - i) % (ringBuffer->bufferLen)])
		{
			flag = FAIL;
		}
	}
	return flag;
}

int PF_CheckRxPacketLength(PF_RING_BUFFER *ringBuffer)
{
	gRxPacketInfo->totallLen = gRxPacketInfo->updateTotalLen(ringBuffer->buffer[(ringBuffer->front + gRxPacketInfo->lenPos) % (ringBuffer->bufferLen)]);

	if(gRxPacketInfo->totallLen <= GetSciRxQueLength(ringBuffer))
	{
		return SUCCESS;
	}
	else
	{
		return FAIL;
	}
}

int PF_GetRingBufferDataSize(PF_RING_BUFFER *ringBuffer)
{
	int length;
	length = (ringBuffer->rear - ringBuffer->front + (ringBuffer->bufferLen)) % (ringBuffer->bufferLen);
	return length;
}

Uint16* PF_SaveRxPacketProfile(Uint16 len, PF_RING_BUFFER *ringBuffer)
{
	int i;

	Uint16* profilePtr = (Uint16*)malloc(sizeof(Uint16) * len);
	if(gRxPacketInfo == NULL)
	{
		//TODO generate alarm
		gmalloc = gmalloc | 0x0200;
		SET_SYS_MEMORY_MOLLOC_ERROR;
		return NULL;
	}

	memset(profilePtr, 0 , sizeof(profilePtr));

	for(i = 0; i < len; ++i)
	{
		profilePtr[i] = ringBuffer->buffer[(ringBuffer->front + i) % (ringBuffer->bufferLen)];
	}

	return profilePtr;
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

void PF_ProcessSciRxPacket(PF_RING_BUFFER *ringBuffer)
{
    Uint16* pfProfilePtr;
	while(PF_GetRingBufferDataSize(ringBuffer) > (gRxPacketInfo->minLen))
	{
		if(PF_FindRxPacketHead(ringBuffer) == FAIL)
		{
			return;
		}

		if(PF_CheckRxPacketLength(ringBuffer) == FAIL)
		{
			return;
		}

		if(PF_FindRxPacketTail(gRxPacketInfo->totallLen, ringBuffer) == FAIL)
		{
			SciRxDeQueue(ringBuffer);
			return;
		}

		pfProfilePtr = PF_SaveRxPacketProfile(gRxPacketInfo->totallLen, ringBuffer);

		if(PF_CalCrc(0, pfProfilePtr + gRxPacketInfo->profileStartPos, gRxPacketInfo->totallLen - gRxPacketInfo->totallLen + 2) != 0)
		{
			free(pfProfilePtr);
			pfProfilePtr = NULL;
			SciRxDeQueue(ringBuffer);
			return;
		}

		PF_UnpackRxProfile(pfProfilePtr, ringBuffer->buffer[(ringBuffer->front + 2) % (ringBuffer->bufferLen)]);

		free(pfProfilePtr);

		pfProfilePtr = NULL;

		PF_UpdateRxQueueHeadPos(gRxPacketInfo->totallLen, ringBuffer);
	}
}
