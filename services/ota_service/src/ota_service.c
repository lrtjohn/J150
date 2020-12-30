#include "ota_service.h"

/*********************************************************************************
 ██████  ████████  █████      ███████ ███████ ██████  ██    ██ ██  ██████ ███████ 
██    ██    ██    ██   ██     ██      ██      ██   ██ ██    ██ ██ ██      ██      
██    ██    ██    ███████     ███████ █████   ██████  ██    ██ ██ ██      █████   
██    ██    ██    ██   ██          ██ ██      ██   ██  ██  ██  ██ ██      ██      
 ██████     ██    ██   ██     ███████ ███████ ██   ██   ████   ██  ██████ ███████ 
*********************************************************************************/
#define OTA_SERVICE_FRAME_ARRAY_LEN     (80)

Uint16 gFrameArray[OTA_SERVICE_FRAME_ARRAY_LEN];

Uint16 OTA_SERVICE_FlashImageData(Uint16 hAddr, Uint16 lAddr, Uint16* flashData, Uint16 len);
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
#if (0)
typedef struct
{
    E_OTA_STATUS        currentStatus;

#if (OTA_TEST == INCLUDE_FEATURE)
    OTA_TEST_VERIFY*    pTestData;
#endif
/* Function poniters define here*/
    ERASE_FLASH_A       pfEraseFlashA;       
    ERASE_FLASH_B       pfEraseFlashB;       
    ERASE_FLASH_G       pfEraseFlashG;    
    IS_OTA_ALLOWED      pfIsOtaAllowed;
    FLASH_LINE_DATA     pfFlashLineData;
    GET_CURRENT_STATUS  pfGetCurrentStatus;

    READ_CUR_VER_NUM    pfReadCurVerNum;
    READ_NEW_VER_NUM    pfReadNewVerNum;

    Uint16*             pImageBitMap;
    Uint16              imageTotalLines;
    Uint16              currentLineNum;
    Uint16              rxLineNum;
    Uint16              lastLineNum;

    OTA_SERVICE_RX_ADAPT    pOtaServiceRxAdapt;

}OTA_SERVICE_ADT;
#endif

OTA_SERVICE_ADT gOtaServiceAdt = 
{
    OTA_SERVICE_IDLE,
#if (OTA_TEST == INCLUDE_FEATURE)
    NULL,
#endif
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,

    NULL,
    NULL,

    NULL,

    0,
    0,
    0,

    NULL,
};

OTA_SERVICE_ADT* pgOtaServiceAdt = NULL;

Uint16 OTA_SERVICE_FIND_RX_HEADER_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfFindHeader(q);
}

Uint16 OTA_SERVICE_CHECK_RX_LEN_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfCheckLen(q);
}

Uint16 OTA_SERVICE_CHECK_RX_CRC_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfCheckSum(q);
}


Uint16 OTA_SERVICE_UPDATE_PAYLOAD_ADAPT(SCIRXQUE* q)
{
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    return pOtaAdtRxAdapt->pfUpdateFrame(q);
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
    }
}

Uint16 OTA_SERVICE_FindRxHeader(SCIRXQUE* q)
{
    while (1)
    {
        if (q->buffer[(q->front) % (q->bufferLen)] != 0x3a) 
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
    Uint16 length;
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;

    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

    if (pOtaAdtRxAdapt == NULL)
    {            
        return 0;
    }

    length = q->buffer[(q->front + 0) % (q->bufferLen)];

    // This is a potencial check if the length valude is too big
    if (length > 0xFF)
    {
        return FAIL;
    }

    pOtaAdtRxAdapt->frameLen = length;

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
    int i;
    Uint16 sum = 0;
    Uint16 checkSumPos = 0;

    // TODO correct the start position when calculate the check sum
    // TODO get the dynamic length
    for (i = 0; i < 0; ++i)
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
    Uint16 opcode;
    OTA_SERVICE_ADT* pOtaAdt;
    OTA_SERVICE_RX_APP *pOtaRxApp;
    // May use global variable to esay to debug
    OTA_SERVICE_RX_ADAPT* pOtaAdtRxAdapt;
    int i;

    pOtaAdt = PTR_OTA_SERVICE_ADT;
    pOtaRxApp = PTR_OTA_SERVICE_ADT_RX_APP;
    pOtaAdtRxAdapt = PTR_OTA_SERVICE_ADT_RX_ADAPT;

#if (1)
    if ((pOtaAdt == NULL) || (pOtaRxApp == NULL) || (pOtaAdtRxAdapt))
    {            
        return 0;
    }

    if (pOtaAdtRxAdapt->frameLen > OTA_SERVICE_FRAME_ARRAY_LEN)
    {
        return 0;
    }

    for (i = 0; i < pOtaAdtRxAdapt->frameLen; ++i)
    {
        gFrameArray[i] = q->buffer[(q->front + i) % (q->bufferLen)];
    }
#endif

    opcode = pOtaAdt->pOtaServiceRxAdapt->pOtaServiceRxApp->pfGetOpcode(gFrameArray);

    if (!(pOtaRxApp->pfIsOpcodeValid(gFrameArray)))
    {
        return 0;
    }

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
            break;
        case OTA_RX_S_CMD:
            if (pOtaAdt->currentStatus != OTA_SERVICE_IDLE)
            {
                /* The S CMD could be recived only when status is IDLE */
                // TODO may need to generate a error code here

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

Uint16 OTA_SERVICE_FlashImageData(Uint16 hAddr, Uint16 lAddr, Uint16* flashData, Uint16 len)
{
    // TODO implement this function later
    Uint32 addr;

    addr = (hAddr << 16 | lAddr);

    return 1;
}
