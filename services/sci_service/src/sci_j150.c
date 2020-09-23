#include "sci_j150.h"
#include <stdio.h>


/*
* J150 protocol layer API
*/
static Uint16 J150_APP_PROTOCOL_GetCommand(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetWorkMode(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetTargetSpeed(unsigned char* data);
static Uint16 J150_APP_PROTOCOL_GetCheckSum(unsigned char* data);
Uint16 J150_APP_PROTOCOL_UnpackPayLoad(void);
/*
* J150 transport layer API
*/
static int J150_TransInit(void);
static int J150_TransConfig(void);
static int J150_TransStart(void);
static int J150_TransFindHead(SCIRXQUE* q);
static int J150_TransCheckLength(SCIRXQUE* q);
static int J150_TransCheckTail(SCIRXQUE* q);
static int J150_TransSaveGoodPacket(int len, SCIRXQUE* q);
static int J150_TransCheckSum(SCIRXQUE* q);
static int J150_TransUpdateHeadPos(SCIRXQUE* q);

/*
* J150 protocol and transport layer global variable
*/
SCI_APP_PROTOCOL* pSciAppProtocol = NULL;

SCI_APP_PROTOCOL gSciAppProtocol_J150 =
{
    {
        HEAD_1_DATA,
        HEAD_2_DATA
    },
    TOTAL_LEN,
    0,
    WORK_MODE_NORMAL,
    0,
    {
        0
    },
    J150_APP_PROTOCOL_GetCommand,
    J150_APP_PROTOCOL_GetWorkMode,
    J150_APP_PROTOCOL_GetTargetSpeed,
    J150_APP_PROTOCOL_GetCheckSum,
    J150_APP_PROTOCOL_UnpackPayLoad
};

SCI_TRANSPORT gSciTrans_J150 =
{
    J150_TransInit,
    J150_TransConfig,
    J150_TransStart,
    J150_TransFindHead,
    J150_TransCheckLength,
    J150_TransCheckTail,
    J150_TransSaveGoodPacket,
    J150_TransCheckSum,
    J150_TransUpdateHeadPos,
};

/*
* API definition
*/
static Uint16 J150_APP_PROTOCOL_GetCommand(unsigned char* data)
{
    Uint16 command;
    
    command = ((data[COMMAND_POS]) << 8) | data[COMMAND_POS + 1];

    return command;
}

static Uint16 J150_APP_PROTOCOL_GetWorkMode(unsigned char* data)
{
    return data[WORK_MODE_POS];
}

static Uint16 J150_APP_PROTOCOL_GetTargetSpeed(unsigned char* data)
{
    Uint16 targetSpeed;
    
    targetSpeed = ((data[TARGET_SPEED_POS]) << 8) | data[TARGET_SPEED_POS + 1];

    return targetSpeed;
}

static Uint16 J150_APP_PROTOCOL_GetCheckSum(unsigned char* data)
{
    return data[CHECK_SUM_POS];
}

Uint16 J150_APP_PROTOCOL_UnpackPayLoad(void)
{
    pSciAppProtocol->command        = pSciAppProtocol->getCommand(pSciAppProtocol->goodPacketArray);
    pSciAppProtocol->workMode       = pSciAppProtocol->getWorkMode(pSciAppProtocol->goodPacketArray);
    pSciAppProtocol->targetSpeed    = pSciAppProtocol->getTargetSpeed(pSciAppProtocol->goodPacketArray);

    if(!IS_PAYLOAD_GOOD(pSciAppProtocol->workMode, pSciAppProtocol->command, pSciAppProtocol->targetSpeed))
    {
        /* TODO If payload parameters is illeagle, need to generate a warining */
        return 0;
    }

    switch(pSciAppProtocol->command)
    {
        case COMMAND_PARA_CONFIG:
            /* Update the work mode and target speed here */
            break;

        case COMMAND_MOTOR_START:
            /* Ignore the work mode and target speed parameters */
            break;

        case COMMAND_MOTOR_STOP:
            /* Ignore the work mode and target speed parameters */
            break;
        
        default:
            break;
    }


    return 0;
}

static int J150_TransInit(void)
{
    return SUCCESS;
}

static int J150_TransConfig(void)
{
    return SUCCESS;
}

static int J150_TransStart(void)
{
    return SUCCESS;
}

static int J150_TransFindHead(SCIRXQUE* q)
{
    while(1)
    {
        if(q->buffer[q->front] == pSciAppProtocol->head[0] && 
            q->buffer[(q->front + 1) % (q->bufferLen)] == pSciAppProtocol->head[1])
        {
            return SUCCESS;
        }

        if(SciRxDeQueue(q) == 0)
        {
            return FAIL;
        }
    }
}

static int J150_TransCheckLength(SCIRXQUE* q)
{
    if(q->buffer[(q->front + TOTAL_LEN_POS) % (q->bufferLen)] != pSciAppProtocol->totalLen)
    {
        SciRxDeQueue(q);
        return FAIL;
    }

    if(GetSciRxQueLength(q) >= pSciAppProtocol->totalLen)
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

static int J150_TransCheckTail(SCIRXQUE* q)
{
    /* J150 doesn't need to check the Tail, so always return success here */
    return SUCCESS;
}

static int J150_TransSaveGoodPacket(int len, SCIRXQUE* q)
{
    int i;

    for(i = 0; i < pSciAppProtocol->totalLen; ++i)
    {
        pSciAppProtocol->goodPacketArray[i] = q->buffer[(q->front + i) % (q->bufferLen)];
    }

    return SUCCESS;
}

static int J150_TransCheckSum(SCIRXQUE* q)
{
    int i;
    Uint16 sum = 0;

    for(i = TOTAL_LEN_POS; i < pSciAppProtocol->totalLen - 1; ++i)
    {
        sum += q->buffer[(q->front + i) % (q->bufferLen)];
    }

    sum |= 0x00ff;

    if(sum == pSciAppProtocol->goodPacketArray[CHECK_SUM_POS])
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

static int J150_TransUpdateHeadPos(SCIRXQUE* q)
{
    q->front = (q->front + pSciAppProtocol->totalLen) % (q->bufferLen);

    return SUCCESS;
}


Uint16 SCI_APP_PROTOCOL_GetLength()
{
    return pSciAppProtocol->totalLen;
}

unsigned char* SCI_APP_PROTOCOL_GetGoodPacketArray()
{
    return pSciAppProtocol->goodPacketArray;
}

void SCI_APP_PROTOCOL_Init(SCI_APP_PROTOCOL* appProtocol)
{
    pSciAppProtocol = appProtocol; 
}

void J150_SCI_UnpackData(SCIRXQUE* q)
{
    while(GetSciRxQueLength(q) >= SCI_APP_PROTOCOL_GetLength());
    {
        if(SCI_Trans_Adapt_FindHead(q) == FAIL)
        {
            return;
        }

        if(SCI_Trans_Adapt_CheckLength(q) == FAIL)
        {
            return;
        }

        if(SCI_Trans_Adapt_CheckTail(q) == FAIL)
        {
            if(SciRxDeQueue(q) == 0)
            {

            }
            return;
        }

        if(SCI_Trans_Adapt_CheckSum(q) == FAIL)
        {
            if(SciRxDeQueue(q) == 0)
            {

            }
            return;
        }

        SCI_Trans_Adapt_SaveGoodPacket(SCI_APP_PROTOCOL_GetLength(), q);

        SCI_Trans_Adapt_UpdateHeadPos(q);
    }
}
