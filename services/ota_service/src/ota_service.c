#include "ota_service.h"

/*********************************************************************************
 ██████  ████████  █████      ███████ ███████ ██████  ██    ██ ██  ██████ ███████ 
██    ██    ██    ██   ██     ██      ██      ██   ██ ██    ██ ██ ██      ██      
██    ██    ██    ███████     ███████ █████   ██████  ██    ██ ██ ██      █████   
██    ██    ██    ██   ██          ██ ██      ██   ██  ██  ██  ██ ██      ██      
 ██████     ██    ██   ██     ███████ ███████ ██   ██   ████   ██  ██████ ███████ 
*********************************************************************************/
#define OTA_SERVICE_FRAME_ARRAY_LEN     (80)

Uint16 gFrameArray[OTA_SERVICE_FRAME_ARRAY_LEN] = {0};
Uint16 gFrameArrayFlash[OTA_SERVICE_FRAME_ARRAY_LEN] = {0};
Uint16 gOtaTxFrameArray[OTA_SERVICE_TX_ONE_FRAME_SIZE] = 
{
    0x5a,
    0x5a,
    0x01,
    0xff,
    0xff,
    0xf2,
    0x00,
    0x00,
    0x00,
    0x00,
    0xa5,
    0xa5
};
Uint16 gImageBitMap[OTA_SERVICE_RX_IMAGE_SIZE] = {0};

Uint16 OTA_SERVICE_FlashImageData(Uint16 hAddr, Uint16 lAddr, Uint16* flashData, Uint16 len);
Uint16 OTA_SERVICE_EraseFlash(Uint16 sector);
void OTA_SERVICE_RxDataToFlashData(Uint16 len);

static Uint16 OTA_SERVICE_FIND_RX_HEADER_ADAPT(SCIRXQUE* q);
static Uint16 OTA_SERVICE_CHECK_RX_LEN_ADAPT(SCIRXQUE* q);
static Uint16 OTA_SERVICE_CHECK_RX_CRC_ADAPT(SCIRXQUE* q);
static Uint16 OTA_SERVICE_UPDATE_PAYLOAD_ADAPT(SCIRXQUE* q);
static Uint16 OTA_SERVICE_UPDATE_HEAD_POS_ADAPT(SCIRXQUE* q);

Uint16 OTA_SERVICE_EraseB(void);
Uint16 OTA_SERVICE_EraseA(void);
Uint16 OTA_SERVICE_EraseG(void);

Uint16 OTA_SERVICE_FindRxHeader(SCIRXQUE* q);
Uint16 OTA_SERVICE_CheckLen(SCIRXQUE* q);
Uint16 OTA_SERVICE_CheckSum(SCIRXQUE* q);
Uint16 OTA_SERVICE_ProcessOneFrame(SCIRXQUE* q);
Uint16 OTA_SERVICE_UpdateHeadPos(SCIRXQUE* q);

Uint16 OTA_SERVICE_GetOpcode(Uint16* data);
Uint16 OTA_SERVICE_IsOpcodeValid(Uint16* array);
Uint16 OTA_SERVICE_WriteFlashOneFrame(Uint32 addr, Uint16 *data, Uint16 len);
Uint16 OTA_SERVICE_UpdateHighAddr(Uint16 *data, Uint16 len);
Uint16 OTA_SERVICE_UpdateLowAddr(Uint16 *data, Uint16 len);

Uint16 OTA_SERVICE_SendSerialNum(void);
Uint16 OTA_SERVICE_GetCurrentStatus(void);
Uint16 OTA_SERVICE_CheckAddr(Uint32 addr);
void OTA_SERVICE_SystemReboot(void);

Uint16 OTA_SERVICE_TxCalCrc(Uint16 crc, const char* buf, Uint16 len);
Uint16 OTA_SERVICE_TxEnQueOneFrame(SCITXQUE* txQue);

#if (OTA_TEST == INCLUDE_FEATURE)
OTA_TEST_VERIFY gOtaServiceTestData = 
{
    A_SECTOR_28_START,
    A_SECTOR_28_LEN,
    A_SECTOR_28_END,

    B_SECTOR_28_START,
    B_SECTOR_28_LEN,
    B_SECTOR_28_END,

    C_SECTOR_28_START,
    C_SECTOR_28_LEN,
    C_SECTOR_28_END,

    D_SECTOR_28_START,
    D_SECTOR_28_LEN,
    D_SECTOR_28_END,

    E_SECTOR_28_START,
    E_SECTOR_28_LEN,
    E_SECTOR_28_END,

    F_SECTOR_28_START,
    F_SECTOR_28_LEN,
    F_SECTOR_28_END,

    G_SECTOR_28_START,
    G_SECTOR_28_LEN,
    G_SECTOR_28_END,

    H_SECTOR_28_START,
    H_SECTOR_28_LEN,
    H_SECTOR_28_END,

    USER_BOOTLOADER_START_ADDR,
    USER_BOOTLOADER_LEN,
    USER_BOOTLOADER_END_ADDR,

    A_APPLICATION_START_ADDR,
    A_APPLICATION_LEN,
    A_APPLICATION_END_ADDR,

    B_APPLICATION_START_ADDR,
    B_APPLICATION_LEN,
    B_APPLICATION_END_ADDR,

    GLOBAL_START_ADDR,
    GLOBAL_LEN,
    GLOBAL_END_ADDR,

    DLETA_BETWEEN_A_AND_B,
};

void OTA_SERVICE_TestData(void)
{
    gOtaServiceTestData.aStart              = 0;
    gOtaServiceTestData.aLen                = 0;
    gOtaServiceTestData.aEnd                = 0;

    gOtaServiceTestData.bStart              = 0;
    gOtaServiceTestData.bLen                = 0;
    gOtaServiceTestData.bEnd                = 0;

    gOtaServiceTestData.cStart              = 0;
    gOtaServiceTestData.cLen                = 0;
    gOtaServiceTestData.cEnd                = 0;

    gOtaServiceTestData.dStart              = 0;
    gOtaServiceTestData.dLen                = 0;
    gOtaServiceTestData.dEnd                = 0;

    gOtaServiceTestData.eStart              = 0;
    gOtaServiceTestData.eLen                = 0;
    gOtaServiceTestData.eEnd                = 0;

    gOtaServiceTestData.fStart              = 0;
    gOtaServiceTestData.fLen                = 0;
    gOtaServiceTestData.fEnd                = 0;

    gOtaServiceTestData.gStart              = 0;
    gOtaServiceTestData.gLen                = 0;
    gOtaServiceTestData.gEnd                = 0;

    gOtaServiceTestData.hStart              = 0;
    gOtaServiceTestData.hLen                = 0;
    gOtaServiceTestData.hEnd                = 0;

    gOtaServiceTestData.userBootStart       = 0;
    gOtaServiceTestData.userBootLen         = 0;
    gOtaServiceTestData.userBootEnd         = 0;

    gOtaServiceTestData.userAppAStart       = 0;
    gOtaServiceTestData.userAppALen         = 0;
    gOtaServiceTestData.userAppAEnd         = 0;

    gOtaServiceTestData.userAppBStart       = 0;
    gOtaServiceTestData.userAppBLen         = 0;
    gOtaServiceTestData.userAppBEnd         = 0;

    gOtaServiceTestData.GlobalStart         = 0;
    gOtaServiceTestData.GlobalLen           = 0;
    gOtaServiceTestData.GlobalEnd           = 0;

    gOtaServiceTestData.Delta               =0;
}
#endif /* (OTA_TEST == INCLUDE_FEATURE) */

OTA_SERVICE_LOG_CNT gOtaServiceLogCnt = 
{
    .serialNum      = 0,
    .writeFailCnt   = 0,
    .eraseFailCnt   = 0,
};

OTA_SERVICE_RX_APP gOtaServiceRxApp =
{
    .pfGetOpcode        = OTA_SERVICE_GetOpcode,
    .pfIsOpcodeValid    = OTA_SERVICE_IsOpcodeValid,
    .pfFlashImageData   = OTA_SERVICE_WriteFlashOneFrame,
    .pfUpdateHighAddr   = OTA_SERVICE_UpdateHighAddr,
    .pfUpdateLowAddr    = OTA_SERVICE_UpdateLowAddr,
    .opcode             = 0,
    .lAddr              = 0,
    .hAddr              = 0,
    .addr               ={0},
};

OTA_SERVICE_RX_ADAPT gOtaServiceRxAdapt =
{
    .pfFindHeader       = OTA_SERVICE_FindRxHeader,
    .pfCheckLen         = OTA_SERVICE_CheckLen,
    .pfCheckSum         = OTA_SERVICE_CheckSum,
    .pfUpdateFrame      = OTA_SERVICE_ProcessOneFrame,
    .pfUpdateHeadPos    = OTA_SERVICE_UpdateHeadPos,
    .pfRxAdapt          = OTA_SERVICE_PROCESS_RX_DATA_ADAPT,
    .pOtaServiceRxApp   = &gOtaServiceRxApp,
    .rxFrameLen         = 0,
    .headerLen          = 0,
    .tailLen            = 0,
    .extraLen           = 0,
};

OTA_SERVICE_ADT gOtaServiceAdt = 
{
    .currentStatus      = OTA_SERVICE_IDLE, /* If system hss two kind of protocols, the default current status should be disabled*/
#if (OTA_TEST == INCLUDE_FEATURE)
    .pTestData          = &gOtaServiceTestData,
#endif
    .pfEraseFlashA      = OTA_SERVICE_EraseA,
    .pfEraseFlashB      = OTA_SERVICE_EraseB,
    .pfEraseFlashG      = OTA_SERVICE_EraseG,
    .pfIsOtaAllowed     = NULL,
    .pfFlashLineData    = NULL,
    .pfGetCurrentStatus = OTA_SERVICE_GetCurrentStatus,
    .pfSystemReboot     = OTA_SERVICE_SystemReboot,
    .pfSendSerialNum    = OTA_SERVICE_SendSerialNum,
    .pfCheckAddr        = OTA_SERVICE_CheckAddr,

    .pfReadCurVerNum    = NULL,
    .pfReadNewVerNum    = NULL,

    .pImageBitMap       = gImageBitMap,
    .imageTotalLines    = 0,
    .currentLineNum     = 0,
    .rxLineNum          = 0,
    .lastLineNum        = 0,

    .areaSectorB        = OTA_SERVICE_B_AREA_SECTOR,
    .areaSectorA        = OTA_SERVICE_A_AREA_SECTOR,
    .areaSectorG        = OTA_SERVICE_G_AREA_SECTOR,

    .pOtaServiceRxAdapt = &gOtaServiceRxAdapt,
    .pOtaSeviceLogCnt   = &gOtaServiceLogCnt,
};

OTA_SERVICE_ADT* pgOtaServiceAdt = NULL;

static Uint16 OTA_SERVICE_FIND_RX_HEADER_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfFindHeader(q);
}

static Uint16 OTA_SERVICE_CHECK_RX_LEN_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfCheckLen(q);
}

static Uint16 OTA_SERVICE_CHECK_RX_CRC_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfCheckSum(q);
}


static Uint16 OTA_SERVICE_UPDATE_PAYLOAD_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfUpdateFrame(q);
}

static Uint16 OTA_SERVICE_UPDATE_HEAD_POS_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfUpdateHeadPos(q);
}
/* This function is mainly used for process the rx data for OTA service */
/* This function should be called in the main loop and after received the OTA start cmd */ 
void OTA_SERVICE_PROCESS_RX_DATA_ADAPT(SCIRXQUE* q)
{
    /*
     * Step 1: Find Frame header
     * Step 2: Frame length check
     * Step 3: CRC or checksum check 
     * Step 4: Process the payload 
     * Step 5: Call different API based on the Rx protocol 
     * Step 6: Update the OTA service status which need to send to the upper layer 
     * Step 7: Update the state machine of the OTA service 
     */
    while (GetSciRxQueLength(q) >= OTA_SERVICE_RX_EXTRA_LEN)
    {
        if (!OTA_SERVICE_FIND_RX_HEADER_ADAPT(q))
        {
            return;
        }

        if (!OTA_SERVICE_CHECK_RX_LEN_ADAPT(q))
        {
            return;
        }

        if (!OTA_SERVICE_CHECK_RX_CRC_ADAPT(q))
        {
            return;
        }

        OTA_SERVICE_UPDATE_PAYLOAD_ADAPT(q);

        OTA_SERVICE_UPDATE_HEAD_POS_ADAPT(q);
    }
}

Uint16 OTA_SERVICE_FindRxHeader(SCIRXQUE* q)
{
    while (1)
    {
        if (q->buffer[(q->front) % (q->bufferLen)] != OTA_SERVICE_RX_HEAD_DATA) 
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

Uint16 OTA_SERVICE_CheckLen(SCIRXQUE* q)
{
    /* Decide to use dynamic length instead of fixed length  */

    // TODO determine the length position
    // Should get the dynamic length here and update the length value,
    // then just wait until meet the length requirement
    Uint16                  length;
    OTA_SERVICE_RX_ADAPT    *pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    length = q->buffer[(q->front + 0) % (q->bufferLen)];

    // This is a potencial check if the length value is too big
    if (length > 0xFF)
    {
        return FAIL;
    }

    pOtaAdtRxAdapt->rxFrameLen = length;

    // TODO determine the length value 
    // Maybe there should be a extra lenght here
    if (GetSciRxQueLength(q) >= length)
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

Uint16 OTA_SERVICE_CheckSum(SCIRXQUE* q)
{
    Uint16 i;
    Uint16 sum = 0;
    Uint16 checkSumPos = 0;

    // TODO correct the start position when calculate the check sum
    // TODO get the dynamic length
    for (i = 0; i < 1; ++i)
    {
        sum += q->buffer[(q->front + i) % (q->bufferLen)];
    }

    sum &= 0x00ff;

    checkSumPos = q->buffer[(q->front + 0) % (q->bufferLen)];

    if (sum == q->buffer[((q->front) + checkSumPos) % (q->bufferLen)])
    {
        return SUCCESS;
    }
    else
    {
        return FAIL;
    }
}

Uint16 OTA_SERVICE_ProcessOneFrame(SCIRXQUE* q)
{
    Uint16                  i;
    Uint16                  opcode;
    OTA_SERVICE_ADT         *pOtaAdt;
    OTA_SERVICE_RX_APP      *pOtaRxApp;
    OTA_SERVICE_RX_ADAPT    *pOtaAdtRxAdapt;

    pOtaAdt         = PTR_OTA_SERVICE_ADT;
    pOtaRxApp       = PTR_OTA_SERVICE_ADT_RX_APP;
    pOtaAdtRxAdapt  = PTR_OTA_SERVICE_ADT_RX_ADAPT;

#if (OTA_PTR_NULL_CHECK == INCLUDE_FEATURE)
    if ((pOtaAdt == NULL) || (pOtaRxApp == NULL) || (pOtaAdtRxAdapt))
    {            
        return 0;
    }

    if (pOtaAdtRxAdapt->rxFrameLen > OTA_SERVICE_FRAME_ARRAY_LEN)
    {
        return 0;
    }
#endif

    for (i = 0; i < pOtaAdtRxAdapt->rxFrameLen; ++i)
    {
        gFrameArray[i] = q->buffer[(q->front + i) % (q->bufferLen)];
    }

    opcode = pOtaAdt->pOtaServiceRxAdapt->pOtaServiceRxApp->pfGetOpcode(gFrameArray);

    if (!(pOtaRxApp->pfIsOpcodeValid(gFrameArray)))
    {
        return 0;
    }
    
    pOtaAdt->pfSendSerialNum();

    switch(opcode)
    {
        case OTA_UD_H_ADDR:
            if (pOtaAdt->currentStatus == OTA_SERVICE_RX_START_CMD)
            {
                pOtaAdt->currentStatus = OTA_SERVICE_RUNNING;
            }

            if (pOtaAdt->currentStatus != OTA_SERVICE_RUNNING)
            {
                return 0;
            }

            // TODO FW need to add a offset of the data buffer
            pOtaRxApp->pfUpdateHighAddr(gFrameArray, pOtaAdtRxAdapt->rxFrameLen);

            break;
        case OTA_UD_F_DATA:
            if (pOtaAdt->currentStatus == OTA_SERVICE_RX_START_CMD)
            {
                pOtaAdt->currentStatus = OTA_SERVICE_RUNNING;
            }

            if (pOtaAdt->currentStatus != OTA_SERVICE_RUNNING)
            {
                return 0;
            }

            // TODO FW need to add a offset of the data buffer
            pOtaRxApp->pfUpdateLowAddr(gFrameArray, pOtaAdtRxAdapt->rxFrameLen);
            pOtaRxApp->pfFlashImageData(pOtaRxApp->addr.value, gFrameArray, pOtaAdtRxAdapt->rxFrameLen);

            break;
        case OTA_RX_S_CMD:
            if (pOtaAdt->currentStatus != OTA_SERVICE_IDLE)
            {
                /* The S CMD could be recived only when status is IDLE */
                // TODO may need to generate a error code here
                return 0;
            }

            if (!(pOtaAdt->pfEraseFlashB()))
            {
                // TODO What should FW do if erase flash failed?
                return 0;
            }

            // TODO need to check the system state machine state is stop or not
            pOtaAdt->currentStatus = OTA_SERVICE_RX_START_CMD;
            break;
        case OTA_RX_E_CMD:
            if (pOtaAdt->currentStatus != OTA_SERVICE_RUNNING)
            {
                return 0;
            }
            pOtaAdt->currentStatus = OTA_SERVICE_END;
            pOtaAdt->pfSystemReboot();
            break;
        case OTA_RX_RFU1:
            break;
        case OTA_RX_RFU2:
            break;
        case OTA_RX_RFU3:
            break;
        case OTA_RX_RFU4:
            break;
        default:
            break;
    }

    return 1;
}

Uint16 OTA_SERVICE_UpdateHeadPos(SCIRXQUE* q)
{
    Uint16 len;

    len = PTR_OTA_SERVICE_ADT_RX_ADAPT->rxFrameLen;

    q->front = (q->front + len) % (q->bufferLen);

    return 1;
}

Uint16 OTA_SERVICE_EraseFlash(Uint16 sector)
{
    Uint16 ret;
    FLASH_ST flashStatus;

    // TODO FW need to disable watch dog here,
    // Because the erase flash may takes a long time and caused the system reboot.
    OTA_SERVICE_INTERRUPT_DISABLE();

    ret = Flash_Erase(sector, &flashStatus);

    OTA_SERVICE_INTERRUPT_ENABLE();

    return ret;
}


Uint16 OTA_SERVICE_EraseA(void)
{
    // TODO need more check for the pointer
    return OTA_SERVICE_EraseFlash(PTR_OTA_SERVICE_ADT->areaSectorA);
}

Uint16 OTA_SERVICE_EraseB(void)
{
    // TODO need more check for the pointer
    return OTA_SERVICE_EraseFlash(PTR_OTA_SERVICE_ADT->areaSectorB);
}

Uint16 OTA_SERVICE_EraseG(void)
{
    return OTA_SERVICE_EraseFlash(PTR_OTA_SERVICE_ADT->areaSectorG);
}

Uint16 OTA_SERVICE_UpdateHighAddr(Uint16 *data, Uint16 len)
{
    Uint16 ret;

    // TODO replace the 0 and 1 later, user the position of high addr instead
    ret = (data[0] << 8) | data[1];
    (PTR_OTA_SERVICE_ADT_RX_APP)->addr.uAddr32.high16Bit = ret;

    return ret;
}

Uint16 OTA_SERVICE_UpdateLowAddr(Uint16 *data, Uint16 len)
{
    Uint16 ret;

    // TODO replace the 0 and 1 later, user the position of low addr instead
    ret = (data[0] << 8) | data[1];
    (PTR_OTA_SERVICE_ADT_RX_APP)->addr.uAddr32.low16Bit = ret;

    return ret;
}

Uint16 OTA_SERVICE_FlashWriteAndVerify(Uint32 addr, Uint16 *buffer, Uint16 len)
{
    Uint16      *addrTemp = 0;
    FLASH_ST    flashStatus;
    Uint16      status = 1;

    addrTemp = (Uint16*)addr;

    status = Flash_Program(addrTemp, buffer, len, &flashStatus);

    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    status = 1;

    status = Flash_Verify(addrTemp, buffer, len, &flashStatus);

    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    return STATUS_SUCCESS;
}

Uint16 OTA_SERVICE_WriteFlashOneFrame(Uint32 addr, Uint16 *data, Uint16 len)
{
    Uint16 ret;

    OTA_SERVICE_INTERRUPT_DISABLE();

    ret =  OTA_SERVICE_FlashWriteAndVerify(addr, data, len);

    // TODO if ret equals to FAIL, FW may could have a secode try writing

    OTA_SERVICE_INTERRUPT_ENABLE();

    return ret;
}

void OTA_SERVICE_RxDataToFlashData(Uint16 len)
{
    Uint16 i;

    for (i = 0; i < ((len - OTA_SERVICE_RX_EXTRA_LEN) >> 1); ++i)
    {
        gFrameArrayFlash[i] = (gFrameArray[OTA_SERVICE_RX_FLASH_DATA_LEN * i + OTA_SERVICE_RX_FLASH_DATAH_OFFSET] << 8) | 
                              (gFrameArray[OTA_SERVICE_RX_FLASH_DATA_LEN * i + OTA_SERVICE_RX_FLASH_DATAL_OFFSET]);
    }
}

void OTA_SERVICE_SystemReboot(void)
{
    // TODO FW need to set a flag to indicate that there is a new FW need to update
    // TODO disable the watch dog to force the system reboot
}

Uint16 OTA_SERVICE_GetOpcode(Uint16* data)
{
    return 0;
}

Uint16 OTA_SERVICE_IsOpcodeValid(Uint16* array)
{
    return 0;
}

Uint16 OTA_SERVICE_GetCurrentStatus(void)
{
    return PTR_OTA_SERVICE_ADT->currentStatus;
}

Uint16 OTA_SERVICE_SendSerialNum(void)
{
    PTR_OTA_SERVICE_ADT->rxLineNum++;
    return 0;
}

Uint16 OTA_SERVICE_CheckAddr(Uint32 addr)
{
    /*
     *  There is a potencial risk that the flash address maybe the password area
     *  This could leads the password area corrupted.
     *  TI 28x chip would locked if the password area is flashed not by purpose
     *  So FW need to abort the flash data if the address is OOR.
     */

    if ((addr >= PROTECT_START_ADDR) &&
        (addr <= PROTECT_END_ADDR)
        )
    {
        return 0;
    }

    return 1;
}


void OTA_SERVICE_TxPackData(SCITXQUE* txQue)
{
    // TODO, maybe could do it simple.
    // because the OTA sending packet is not complicated.
}

Uint16 OTA_SERVICE_TxCalCrc(Uint16 crc, const char* buf, Uint16 len)
{
    int x;
    int i;

    for (i = 0; i < len; ++i)
    {
        x = ((crc >> 8) ^ buf[i]) & 0xFF;
        x ^= x >> 4;
        crc = (crc << 8) ^ (x << 12) ^ (x << 5) ^ x;
        crc &= 0xFFFF;
    }

    return crc;
}

Uint16 OTA_SERVICE_TxEnQueOneFrame(SCITXQUE* txQue)
{
    int i;

    for (i = 0; i < OTA_SERVICE_TX_ONE_FRAME_SIZE; ++i)
    {
        if (SciTxEnQueue(gOtaTxFrameArray[i], txQue) == 0)
        {
            return 0;
        }
    }

    return 1;
}
