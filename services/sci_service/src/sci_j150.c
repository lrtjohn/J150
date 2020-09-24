#include "sci_j150.h"
#include <stdio.h>

/******************************************************************************************************************************************************
    /$$$$$   /$$   /$$$$$$$   /$$$$$$         /$$$$$$   /$$$$$$  /$$$$$$       /$$$$$$$  /$$$$$$$   /$$$$$$  /$$$$$$$$/$$$$$$   /$$$$$$   /$$$$$$  /$$      
   |__  $$ /$$$$  | $$____/  /$$$_  $$       /$$__  $$ /$$__  $$|_  $$_/      | $$__  $$| $$__  $$ /$$__  $$|__  $$__/$$__  $$ /$$__  $$ /$$__  $$| $$      
      | $$|_  $$  | $$      | $$$$\ $$      | $$  \__/| $$  \__/  | $$        | $$  \ $$| $$  \ $$| $$  \ $$   | $$ | $$  \ $$| $$  \__/| $$  \ $$| $$      
      | $$  | $$  | $$$$$$$ | $$ $$ $$      |  $$$$$$ | $$        | $$        | $$$$$$$/| $$$$$$$/| $$  | $$   | $$ | $$  | $$| $$      | $$  | $$| $$      
 /$$  | $$  | $$  |_____  $$| $$\ $$$$       \____  $$| $$        | $$        | $$____/ | $$__  $$| $$  | $$   | $$ | $$  | $$| $$      | $$  | $$| $$      
| $$  | $$  | $$   /$$  \ $$| $$ \ $$$       /$$  \ $$| $$    $$  | $$        | $$      | $$  \ $$| $$  | $$   | $$ | $$  | $$| $$    $$| $$  | $$| $$      
|  $$$$$$/ /$$$$$$|  $$$$$$/|  $$$$$$/      |  $$$$$$/|  $$$$$$/ /$$$$$$      | $$      | $$  | $$|  $$$$$$/   | $$ |  $$$$$$/|  $$$$$$/|  $$$$$$/| $$$$$$$$
 \______/ |______/ \______/  \______/        \______/  \______/ |______/      |__/      |__/  |__/ \______/    |__/  \______/  \______/  \______/ |________/
********************************************************************************************************************************************************/

/*
* J150 protocol layer API
*/
static Uint16 J150_APP_RX_PROTOCOL_GetCommand(unsigned char* data);
static Uint16 J150_APP_RX_PROTOCOL_GetWorkMode(unsigned char* data);
static Uint16 J150_APP_RX_PROTOCOL_GetTargetSpeed(unsigned char* data);
static Uint16 J150_APP_RX_PROTOCOL_GetCheckSum(unsigned char* data);
Uint16 J150_APP_RX_PROTOCOL_UnpackPayLoad(void);
/*
* J150 transport layer API
*/
static int J150_TransRxInit(void);
static int J150_TransRxConfig(void);
static int J150_TransRxStart(void);
static int J150_TransRxFindHead(SCIRXQUE* q);
static int J150_TransRxCheckLength(SCIRXQUE* q);
static int J150_TransRxCheckTail(SCIRXQUE* q);
static int J150_TransRxSaveGoodPacket(int len, SCIRXQUE* q);
static int J150_TransRxCheckSum(SCIRXQUE* q);
static int J150_TransRxUpdateHeadPos(SCIRXQUE* q);

/*
* J150 protocol and transport layer global variable
*/
SCI_APP_PROTOCOL_RX* pSciAppProtocol = NULL;

SCI_APP_PROTOCOL_RX gSciAppProtocolRx_J150 =
{
    {
        HEAD_1_DATA,
        HEAD_2_DATA
    },
    TOTAL_LEN,
    COMMAND_PARA_NONE,
    WORK_MODE_NORMAL,
    RX_MIN_TARGET_SPEED ,                  /*init target speed*/
    {
        0                                  /* good packet array */
    },
    J150_APP_RX_PROTOCOL_GetCommand,
    J150_APP_RX_PROTOCOL_GetWorkMode,
    J150_APP_RX_PROTOCOL_GetTargetSpeed,
    J150_APP_RX_PROTOCOL_GetCheckSum,
    J150_APP_RX_PROTOCOL_UnpackPayLoad
};

SCI_TRANSPORT_RX gSciTransRx_J150 =
{
    J150_TransRxInit,
    J150_TransRxConfig,
    J150_TransRxStart,
    J150_TransRxFindHead,
    J150_TransRxCheckLength,
    J150_TransRxCheckTail,
    J150_TransRxSaveGoodPacket,
    J150_TransRxCheckSum,
    J150_TransRxUpdateHeadPos,
};

/*
* API definition
*/
static Uint16 J150_APP_RX_PROTOCOL_GetCommand(unsigned char* data)
{
    Uint16 command;
    
    command = ((data[COMMAND_POS]) << 8) | data[COMMAND_POS + 1];

    return command;
}

static Uint16 J150_APP_RX_PROTOCOL_GetWorkMode(unsigned char* data)
{
    return data[WORK_MODE_POS];
}

static Uint16 J150_APP_RX_PROTOCOL_GetTargetSpeed(unsigned char* data)
{
    Uint16 targetSpeed;
    
    targetSpeed = ((data[TARGET_SPEED_POS]) << 8) | data[TARGET_SPEED_POS + 1];

    return targetSpeed;
}

static Uint16 J150_APP_RX_PROTOCOL_GetCheckSum(unsigned char* data)
{
    return data[CHECK_SUM_POS];
}

Uint16 J150_APP_RX_PROTOCOL_UnpackPayLoad(void)
{
    Uint16 command;
    Uint16 workMode;
    Uint16 targetSpeed;

    command        = pSciAppProtocol->getCommand(pSciAppProtocol->goodPacketArray);
    workMode       = pSciAppProtocol->getWorkMode(pSciAppProtocol->goodPacketArray);
    targetSpeed    = pSciAppProtocol->getTargetSpeed(pSciAppProtocol->goodPacketArray);

#if (0)
    if(!IS_PAYLOAD_GOOD(pSciAppProtocol->workMode, pSciAppProtocol->command, pSciAppProtocol->targetSpeed))
    {
        /* TODO If payload parameters is illeagle, need to generate a warining */
        return 0;
    }
#endif

    if(!IS_COMMAND_GOOD(command))
    {
        //TODO rx command is invalid
        return 0;
    }

    pSciAppProtocol->command = (COMMAND_DEFINITION)command;

    switch(command)
    {
        case COMMAND_PARA_CONFIG:
            /* Update the work mode and target speed here */
            if(IS_TARGET_SPEED_GOOD(targetSpeed) &&
                IS_WORK_MODE_GOOD(workMode))
            {
                pSciAppProtocol->targetSpeed = targetSpeed;
                pSciAppProtocol->workMode = (WORKMODE)workMode;
            }
            else
            {
                //TODO target speed or work mode is invalid, generate warining here
            }
            break;

        case COMMAND_MOTOR_START:
            /* Ignore the work mode and target speed parameters */
            pSciAppProtocol->command = (COMMAND_DEFINITION)command;
            break;

        case COMMAND_MOTOR_STOP:
            pSciAppProtocol->command = (COMMAND_DEFINITION)command;
            /* Ignore the work mode and target speed parameters */
            break;
        
        default:
            break;
    }


    return 0;
}

static int J150_TransRxInit(void)
{
    return SUCCESS;
}

static int J150_TransRxConfig(void)
{
    return SUCCESS;
}

static int J150_TransRxStart(void)
{
    return SUCCESS;
}

static int J150_TransRxFindHead(SCIRXQUE* q)
{
    while(1)
    {
        if((q->buffer[q->front] == pSciAppProtocol->head[0]) && 
            (q->buffer[(q->front + 1) % (q->bufferLen)] == pSciAppProtocol->head[1]))
        {
            return SUCCESS;
        }

        if(SciRxDeQueue(q) == 0)
        {
            return FAIL;
        }
    }
}

static int J150_TransRxCheckLength(SCIRXQUE* q)
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

static int J150_TransRxCheckTail(SCIRXQUE* q)
{
    /* J150 doesn't need to check the Tail, so always return success here */
    return SUCCESS;
}

static int J150_TransRxSaveGoodPacket(int len, SCIRXQUE* q)
{
    int i;

    for(i = 0; i < pSciAppProtocol->totalLen; ++i)
    {
        pSciAppProtocol->goodPacketArray[i] = q->buffer[(q->front + i) % (q->bufferLen)];
    }
    J150_APP_RX_PROTOCOL_UnpackPayLoad();
    return SUCCESS;
}

static int J150_TransRxCheckSum(SCIRXQUE* q)
{
    int i;
    Uint16 sum = 0;

    for(i = TOTAL_LEN_POS; i < pSciAppProtocol->totalLen - 1; ++i)
    {
        sum += q->buffer[(q->front + i) % (q->bufferLen)];
    }

    sum &= 0x00ff;

    if(sum == q->buffer[((q->front) + CHECK_SUM_POS) % (q->bufferLen)])
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

static int J150_TransRxUpdateHeadPos(SCIRXQUE* q)
{
    q->front = (q->front + pSciAppProtocol->totalLen) % (q->bufferLen);

    return SUCCESS;
}

Uint16 SCI_APP_RX_PROTOCOL_ADAPT_GetLength()
{
    return pSciAppProtocol->totalLen;
}

unsigned char* SCI_APP_PROTOCOL_GetGoodPacketArray()
{
    return pSciAppProtocol->goodPacketArray;
}

void SCI_APP_PROTOCOL_Init(SCI_APP_PROTOCOL_RX* appProtocol)
{
    pSciAppProtocol = appProtocol; 
}

void J150_SCI_UnpackData(SCIRXQUE* q)
{
    while(GetSciRxQueLength(q) >= SCI_APP_RX_PROTOCOL_ADAPT_GetLength())
    {
        if(SCI_Trans_AdaptRx_FindHead(q) == FAIL)
        {
            return;
        }

        if(SCI_Trans_AdaptRx_CheckLength(q) == FAIL)
        {
            return;
        }

        if(SCI_Trans_AdaptRx_CheckTail(q) == FAIL)
        {
            SciRxDeQueue(q);
            return;
        }

        if(SCI_Trans_AdaptRx_CheckSum(q) == FAIL)
        {
            SciRxDeQueue(q);
            return;
        }

        SCI_Trans_AdaptRx_SaveGoodPacket(SCI_APP_RX_PROTOCOL_ADAPT_GetLength(), q);

        SCI_Trans_AdaptRx_UpdateHeadPos(q);
    }
}
