#include "sci_j150.h"
#include <stdio.h>

/*
* J150 protocol layer API
*/
static Uint16 J150_APP_RX_PROTOCOL_GetCommand(unsigned char* data);
static Uint16 J150_APP_RX_PROTOCOL_GetWorkMode(unsigned char* data);
static Uint16 J150_APP_RX_PROTOCOL_GetTargetSpeed(unsigned char* data);
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
Uint16 gTxFrameArray[SCI_TX_ONE_FRAME_LENGTH] = 
{
    TX_HEAD1_DATA,          // 0
    TX_HEAD2_DATA,          // 1
    TX_LENGTH_DATA,         // 2
    0,                      // 3
    0,                      // 4
    0,                      // 5
    0,                      // 6
    0,                      // 7
    0,                      // 8
    0,                      // 9
    0,                      // 10 
    0,                      // 11 
    0,                      // 12
    0,                      // 13
    0,                      // 14
    0,                      // 15
    0,                      // 16
    0,                      // 17
    0,                      // 18
    0,                      // 19
    0,                      // 20
    0,                      // 21
    0,                      // 22
    0,                      // 23
    0,                      // 24
    0,                      // 25
    0,                      // 26
    0,                      // 27
    0,                      // 28
    0,                      // 29
    0,                      // 30
    0,                      // 31
    0                       // 32
};

SCI_APP_PROTOCOL_RX* pSciRxAppProtocol = NULL;
SCI_APP_PROTOCOL_RX gSciAppProtocolRx_J150 =
{
    COMMAND_PARA_NONE,
    WORK_MODE_NORMAL,
    RX_MIN_TARGET_SPEED ,                  /*init target speed*/
    {
        0                                  /* good packet array */
    },
    J150_APP_RX_PROTOCOL_GetCommand,
    J150_APP_RX_PROTOCOL_GetWorkMode,
    J150_APP_RX_PROTOCOL_GetTargetSpeed,
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
    {
        HEAD_1_DATA,
        HEAD_2_DATA,
    },
    HEAD_LEN,
    {
        0,
        0,
    },
    0,          // tail length
    TOTAL_LEN,
    &gSciAppProtocolRx_J150 
};

/**************************************************************************************************************************
     ██  ██ ███████  ██████      ██████  ██   ██     ██████  ██████   ██████  ████████  ██████   ██████  ██████  ██      
     ██ ███ ██      ██  ████     ██   ██  ██ ██      ██   ██ ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██      
     ██  ██ ███████ ██ ██ ██     ██████    ███       ██████  ██████  ██    ██    ██    ██    ██ ██      ██    ██ ██      
██   ██  ██      ██ ████  ██     ██   ██  ██ ██      ██      ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██      
 █████   ██ ███████  ██████      ██   ██ ██   ██     ██      ██   ██  ██████     ██     ██████   ██████  ██████  ███████ 
****************************************************************************************************************************/
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

Uint16 J150_APP_RX_PROTOCOL_UnpackPayLoad(void)
{
    Uint16 command;
    Uint16 workMode;
    Uint16 targetSpeed;

    command        = pSciRxAppProtocol->getCommand(pSciRxAppProtocol->goodPacketArray);
    workMode       = pSciRxAppProtocol->getWorkMode(pSciRxAppProtocol->goodPacketArray);
    targetSpeed    = pSciRxAppProtocol->getTargetSpeed(pSciRxAppProtocol->goodPacketArray);

#if (0)
    if(!IS_PAYLOAD_GOOD(pSciAppProtocol->workMode, pSciAppProtocol->command, pSciAppProtocol->targetSpeed))
    {
        /* TODO If payload parameters is illeagle, need to generate a warining */
        return 0;
    }
#endif

    if (!IS_COMMAND_GOOD(command))
    {
        //TODO rx command is invalid
        return 0;
    }

    pSciRxAppProtocol->command = (COMMAND_DEFINITION)command;

    switch(command)
    {
        case COMMAND_PARA_CONFIG:
            /* Update the work mode and target speed here */
            if (IS_WORK_MODE_GOOD(workMode))
            {
                pSciRxAppProtocol->workMode = (WORKMODE)workMode;
            }
            else
            {
                //TODO target speed or work mode is invalid, generate warining here
            }
            break;

        case COMMAND_MOTOR_START:
            if (IS_TARGET_SPEED_GOOD(targetSpeed))
            {
                pSciRxAppProtocol->command = (COMMAND_DEFINITION)command;
                pSciRxAppProtocol->targetSpeed = targetSpeed;

            }
            break;

        case COMMAND_MOTOR_STOP:
            pSciRxAppProtocol->command = (COMMAND_DEFINITION)command;
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
    int i;

    while (1)
    {
        for (i = 0; i < gSciTransRx_J150.mRxHeadLength; ++i)
        {
            if (q->buffer[(q->front + i) % (q->bufferLen)] != gSciTransRx_J150.mRxHead[i]) 
            {
                if (SciRxDeQueue(q) == 0)
                {
                    return FAIL;
                }
                break;
            }
        }

        return SUCCESS;
    }
}

static int J150_TransRxCheckLength(SCIRXQUE* q)
{
    if (q->buffer[(q->front + TOTAL_LEN_POS) % (q->bufferLen)] != gSciTransRx_J150.mRxTotalLength)
    {
        SciRxDeQueue(q);
        return FAIL;
    }

    if (GetSciRxQueLength(q) >= gSciTransRx_J150.mRxTotalLength)
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

    for (i = 0; i < gSciTransRx_J150.mRxTotalLength; ++i)
    {
        ((SCI_APP_PROTOCOL_RX*)(gSciTransRx_J150.mpRxAppProtocol))->goodPacketArray[i] = q->buffer[(q->front + i) % (q->bufferLen)];
    }
    J150_APP_RX_PROTOCOL_UnpackPayLoad();
    return SUCCESS;
}

static int J150_TransRxCheckSum(SCIRXQUE* q)
{
    int i;
    Uint16 sum = 0;

    for (i = TOTAL_LEN_POS; i < gSciTransRx_J150.mRxTotalLength - 1; ++i)
    {
        sum += q->buffer[(q->front + i) % (q->bufferLen)];
    }

    sum &= 0x00ff;

    if (sum == q->buffer[((q->front) + CHECK_SUM_POS) % (q->bufferLen)])
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
    q->front = (q->front + gSciTransRx_J150.mRxTotalLength) % (q->bufferLen);

    return SUCCESS;
}

unsigned char* SCI_APP_PROTOCOL_GetGoodPacketArray()
{
    return pSciRxAppProtocol->goodPacketArray;
}

void SCI_APP_PROTOCOL_RX_Init(SCI_APP_PROTOCOL_RX* rxAppProtocol)
{
    pSciRxAppProtocol = rxAppProtocol; 
}

/**************************************************************************************************************************
     ██  ██ ███████  ██████      ████████ ██   ██     ██████  ██████   ██████  ████████  ██████   ██████  ██████  ██      
     ██ ███ ██      ██  ████        ██     ██ ██      ██   ██ ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██      
     ██  ██ ███████ ██ ██ ██        ██      ███       ██████  ██████  ██    ██    ██    ██    ██ ██      ██    ██ ██      
██   ██  ██      ██ ████  ██        ██     ██ ██      ██      ██   ██ ██    ██    ██    ██    ██ ██      ██    ██ ██      
 █████   ██ ███████  ██████         ██    ██   ██     ██      ██   ██  ██████     ██     ██████   ██████  ██████  ███████ 
****************************************************************************************************************************/

static int J150_TransTxInit(void);
static int J150_TransTxConfig(void);
static int J150_TransTxStart(void);
static int J150_TransTxUpdatePayLoad(void);
static int J150_TransTxCalCheckSum(void);
static int J150_SCI_TX_PackOneFrame(void);
static int J150_TransTxEnQueOneFrame(SCITXQUE* txQue);

SCI_APP_PROTOCOL_TX* pSciTxAppProtocol = NULL;
SCI_APP_PROTOCOL_TX gSciAppProtocolTx_J150 =
{
   TX_HEAD1_DATA, 
   TX_HEAD2_DATA, 
   TX_LENGTH_DATA, 
   0,   // Work status
   0,   // System status1
   0,   // System status2
   0,   // Fault status
   0,   // Frame count
   0,   // Traget speed
   0,   // Current speed
   0,   // Bus voltage
   0,   // Bus current
   0,   // Servo temperature
   0,   // Motor temperature
   0,   // Firmware version Number
   0,   // Work Mode
   0,   // RFU
   0    // Check Sum
};

SCI_TRANSPORT_TX gSciTransTx_J150 =
{
    J150_TransTxInit,
    J150_TransTxConfig,
    J150_TransTxStart,
    J150_TransTxUpdatePayLoad,
    J150_TransTxCalCheckSum,
    J150_SCI_TX_PackOneFrame,
    J150_TransTxEnQueOneFrame,   
    {
        TX_HEAD1_DATA,
        TX_HEAD2_DATA,
    },
    2,
    {
        0,
        0
    },
    0,
    TX_LENGTH_DATA,
    &gSciAppProtocolTx_J150,
    gTxFrameArray,
};

static int J150_TransTxInit(void)
{
    return SUCCESS;
}

static int J150_TransTxConfig(void)
{
    return SUCCESS;
}

static int J150_TransTxStart(void)
{
    return SUCCESS;
}

static int J150_TransTxUpdatePayLoad(void)
{
    SCI_APP_PROTOCOL_TX* data;

    data = pSciTxAppProtocol;

    if(data == NULL)
    {
        return FAIL;
    }

    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_WORK_STATUS_POS]), &data->workStatus);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_SYS_STATUS_1_POS]), &data->sysStatus1);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_SYS_STATUS_2_POS]), &data->sysStatus2);
    U32_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_FAULT_STATUS_POS]), &data->faultStatus);
    U32_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_FRAME_CNT_POS]), &data->frameCnt);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_TARGET_SPEED_POS]), &data->targetSpeed);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_CURRENT_SPEED_POS]), &data->currentSpeed);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_BUS_VOLTAGE_POS]), &data->busVoltage);
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_BUS_CURRENT_POS]), &data->busCurrent);
    gSciTransTx_J150.mpTxOneFrameArray[TX_SERVO_TEMP_POS] = data->servoTemp;
    gSciTransTx_J150.mpTxOneFrameArray[TX_MOTOR_TEMP_POS] = data->motorTemp;
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_FW_VERSION_POS]), &data->fwVersionNum);
    gSciTransTx_J150.mpTxOneFrameArray[TX_WORK_MODE_POS] = data->workMode;
    U16_TO_U8(&(gSciTransTx_J150.mpTxOneFrameArray[TX_RFU_POS]), &data->RFU);

    return SUCCESS;
}

static int J150_TransTxCalCheckSum(void)
{
    Uint16 i = 0;
    Uint16 checkSum = 0;

    for (i = TX_LENGTH_POS; i < TX_CHECK_SUM_POS - 1; ++i)
    {
        checkSum += gSciTransTx_J150.mpTxOneFrameArray[i];
    }

    gSciTransTx_J150.mpTxOneFrameArray[TX_CHECK_SUM_POS] = checkSum;

    return SUCCESS;
}

static int J150_SCI_TX_PackOneFrame(void)
{
    /* currently nothing to do in this function */
    return SUCCESS;
}

static int J150_TransTxEnQueOneFrame(SCITXQUE* txQue)
{
    int i;

    for (i = 0; i < gSciTransTx_J150.mTxTotalLength; ++i)
    {
 		if (SciTxEnQueue(gSciTransTx_J150.mpTxOneFrameArray[i], txQue) == 0)
        {
            return FAIL;
        }
    }
    return SUCCESS;
}

void SCI_APP_PROTOCOL_TX_Init(SCI_APP_PROTOCOL_TX* txAppProtocol)
{
    pSciTxAppProtocol = txAppProtocol; 
}
