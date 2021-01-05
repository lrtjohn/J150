#ifndef OTA_SERVICE_H
#define OTA_SERVICE_H

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod_defs.h"
#include "sci_queue.h"
#include "Flash2833x_API_Library.h"
#include <stdlib.h>

/*********************************************************************************
 ██████  ████████  █████      ███████ ███████ ██████  ██    ██ ██  ██████ ███████ 
██    ██    ██    ██   ██     ██      ██      ██   ██ ██    ██ ██ ██      ██      
██    ██    ██    ███████     ███████ █████   ██████  ██    ██ ██ ██      █████   
██    ██    ██    ██   ██          ██ ██      ██   ██  ██  ██  ██ ██      ██      
 ██████     ██    ██   ██     ███████ ███████ ██   ██   ████   ██  ██████ ███████ 
*********************************************************************************/

/* The h file is for the OTA process definition and declaration */
/* The aim is to support the OTA process in the User application */

/*
*  Right now there are two solutions for the OTA process.
*  Solution 1:
*               A,  B,  User_Bootloader
*  Solution 2:
*               A,  B,  User_Bootloader,    Global
*
*  For the solution 2, need to decide how to allocate the Flash for different area
*/

#define OTA_SOLUTION_1              INCLUDE_FEATURE
#define OTA_TEST                    INCLUDE_FEATURE
#define OTA_PTR_NULL_CHECK          INCLUDE_FEATURE

#define A_SECTOR                    BIT_0
#define B_SECTOR                    BIT_1
#define C_SECTOR                    BIT_2
#define D_SECTOR                    BIT_3
#define E_SECTOR                    BIT_4
#define F_SECTOR                    BIT_5
#define G_SECTOR                    BIT_6
#define H_SECTOR                    BIT_7
#define ALL_SECTOR                  (A_SECTOR | B_SECTOR | C_SECTOR | D_SECTOR | E_SECTOR | F_SECTOR | G_SECTOR | H_SECTOR) 

#define OTA_SERVICE_B_AREA_SECTOR   (G_SECTOR | F_SECTOR)
#define OTA_SERVICE_A_AREA_SECTOR   (E_SECTOR | D_SECTOR)
#define OTA_SERVICE_G_AREA_SECTOR   (B_SECTOR | C_SECTOR)

#define TI_28_START_ADDR            (0x300000)
#define TI_28_ONE_SECTOR_LEN        (0x7FFFF)

#define H_SECTOR_28_START           (TI_28_START_ADDR)
#define H_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define H_SECTOR_28_END             (H_SECTOR_28_START + H_SECTOR_28_LEN)

#define G_SECTOR_28_START           (H_SECTOR_28_END + 1)
#define G_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define G_SECTOR_28_END             (G_SECTOR_28_START + G_SECTOR_28_LEN)

#define F_SECTOR_28_START           (G_SECTOR_28_END + 1)
#define F_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define F_SECTOR_28_END             (F_SECTOR_28_START + F_SECTOR_28_LEN)

#define E_SECTOR_28_START           (F_SECTOR_28_END + 1)
#define E_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define E_SECTOR_28_END             (E_SECTOR_28_START + E_SECTOR_28_LEN)

#define D_SECTOR_28_START           (E_SECTOR_28_END + 1)
#define D_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define D_SECTOR_28_END             (D_SECTOR_28_START + D_SECTOR_28_LEN)

#define C_SECTOR_28_START           (D_SECTOR_28_END + 1)
#define C_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define C_SECTOR_28_END             (C_SECTOR_28_START + C_SECTOR_28_LEN)

#define B_SECTOR_28_START           (C_SECTOR_28_END + 1)
#define B_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define B_SECTOR_28_END             (B_SECTOR_28_START + B_SECTOR_28_LEN)

#define A_SECTOR_28_START           (B_SECTOR_28_END + 1)       
#define A_SECTOR_28_LEN             (TI_28_ONE_SECTOR_LEN)
#define A_SECTOR_28_END             (A_SECTOR_28_START + A_SECTOR_28_LEN)

/* 
 * Currently it's a little bit hard to say which solution is better.
 * So probably the best way is just to pick one and have a try.
*/
#if (OTA_SOLUTION_1 == INCLUDE_FEATURE)
#define USER_BOOTLOADER_START_ADDR      (H_SECTOR_28_START)
#define USER_BOOTLOADER_LEN             (1 * TI_28_ONE_SECTOR_LEN)
#define USER_BOOTLOADER_END_ADDR        (USER_BOOTLOADER_START_ADDR + USER_BOOTLOADER_LEN)

#define A_APPLICATION_START_ADDR        (G_SECTOR_28_START)
#define A_APPLICATION_LEN               (2 * TI_28_ONE_SECTOR_LEN)
#define A_APPLICATION_END_ADDR          (A_APPLICATION_START_ADDR + A_APPLICATION_LEN)

#define B_APPLICATION_START_ADDR        (E_SECTOR_28_START)
#define B_APPLICATION_LEN               (2 * TI_28_ONE_SECTOR_LEN)
#define B_APPLICATION_END_ADDR          (B_APPLICATION_START_ADDR + B_APPLICATION_LEN)

#define GLOBAL_START_ADDR               (C_SECTOR_28_START)
#define GLOBAL_LEN                      (2 * TI_28_ONE_SECTOR_LEN)
#define GLOBAL_END_ADDR                 (GLOBAL_START_ADDR + GLOBAL_LEN)
#endif /* #if (OTA_SOLUTION_1 == INCLUDE_FEATURE) */

#define DLETA_BETWEEN_A_AND_B           (0)

#define OTA_SERVICE_RX_EXTRA_LEN        (6)

#define OTA_SERVICE_RX_HEAD_DATA        (0x3a)

#define OTA_SERVICE_RX_HAED_POS         (0)
#define OTA_SERVICE_RX_HAED_LEN         (1)

#define OTA_SERVICE_RX_LEN_POS          (OTA_SERVICE_RX_HAED_POS + OTA_SERVICE_RX_HAED_LEN)
#define OTA_SERVICE_RX_LEN_LEN          (1)

#define OTA_SERVICE_RX_ADDRL_POS        (OTA_SERVICE_RX_LEN_POS + OTA_SERVICE_RX_LEN_LEN)
#define OTA_SERVICE_RX_ADDRL_LEN        (2)

#define OTA_SERVICE_RX_OPCODE_POS       (OTA_SERVICE_RX_ADDRL_POS + OTA_SERVICE_RX_ADDRL_LEN)
#define OTA_SERVICE_RX_OPCODE_LEN       (1)

#define OTA_SERVICE_RX_ADDRH_POS        (OTA_SERVICE_RX_OPCODE_POS + OTA_SERVICE_RX_OPCODE_LEN)
#define OTA_SERVICE_RX_ADDRH_LEN        (2)

#define OTA_SERVICE_RX_SUM_POS          (OTA_SERVICE_RX_OPCODE_POS + OTA_SERVICE_RX_OPCODE_LEN + PTR_OTA_SERVICE_ADT_RX_ADAPT->rxFrameLen + 1)
#define OTA_SERVICE_RX_SUM_LEN          (1)

#define OTA_SERVICE_RX_FLASH_DATAH_OFFSET   (5)
#define OTA_SERVICE_RX_FLASH_DATAL_OFFSET   (6)
#define OTA_SERVICE_RX_FLASH_DATA_LEN       (2)

#define OTA_SERVICE_RX_IMAGE_SIZE           (20)

#if (OTA_TEST == INCLUDE_FEATURE)
typedef struct 
{
    Uint32 aStart;
    Uint32 aLen;
    Uint32 aEnd;
    
    Uint32 bStart;
    Uint32 bLen;
    Uint32 bEnd;

    Uint32 cStart;
    Uint32 cLen;
    Uint32 cEnd;

    Uint32 dStart;
    Uint32 dLen;
    Uint32 dEnd;

    Uint32 eStart;
    Uint32 eLen;
    Uint32 eEnd;

    Uint32 fStart;
    Uint32 fLen;
    Uint32 fEnd;

    Uint32 gStart;
    Uint32 gLen;
    Uint32 gEnd;

    Uint32 hStart;
    Uint32 hLen;
    Uint32 hEnd;

    Uint32 userBootStart;
    Uint32 userBootLen;
    Uint32 userBootEnd;

    Uint32 userAppAStart;
    Uint32 userAppALen;
    Uint32 userAppAEnd;

    Uint32 userAppBStart;
    Uint32 userAppBLen;
    Uint32 userAppBEnd;

    Uint32 GlobalStart;
    Uint32 GlobalLen;
    Uint32 GlobalEnd;

    Uint32 Delta;

}OTA_TEST_VERIFY;

void OTA_SERVICE_TestData(void);
#endif /* #if (OTA_TEST == INCLUDE_FEATURE) */

typedef Uint16(*ERASE_FLASH_A)(void);

typedef Uint16(*ERASE_FLASH_B)(void);

typedef Uint16(*ERASE_FLASH_G)(void);

typedef Uint16(*IS_OTA_ALLOWED)(void);

typedef Uint16(*FLASH_LINE_DATA)(Uint16* pDtata);

typedef Uint16(*GET_CURRENT_STATUS)(Uint16* pDtata);

typedef Uint16(*READ_CUR_VER_NUM)(void);

typedef Uint16(*READ_NEW_VER_NUM)(void);

typedef Uint16(*FIND_HEADER)(SCIRXQUE* q);

typedef Uint16(*CHECK_LEN)(SCIRXQUE* q);

typedef Uint16(*CHECK_SUM)(SCIRXQUE* q);

typedef Uint16(*UPDATE_FRAME)(SCIRXQUE* q);

typedef Uint16(*UPDATE_HEAD_POS)(SCIRXQUE* q);

typedef void(*SYSTEM_REBOOT)(void);

typedef struct
{
    Uint16 serialNum;
    Uint16 writeFailCnt;
    Uint16 eraseFailCnt;
    /* data */
}OTA_SERVICE_LOG_CNT;

typedef struct
{
	Uint32 high16Bit    : 16;
	Uint32 low16Bit	    : 16;
}ADDR32BIT;
typedef union
{
	Uint32          	value;
	ADDR32BIT        	uAddr32;
}OTA_SERVICE_ADDR;

typedef struct 
{
    Uint16(*pfGetOpcode)(Uint16* array);
    Uint16(*pfIsOpcodeValid)(Uint16* array);
    Uint16(*pfFlashImageData)(Uint32 addr, Uint16* data, Uint16 len);
    Uint16(*pfUpdateHighAddr)(Uint16* data, Uint16 len);
    Uint16(*pfUpdateLowAddr)(Uint16* data, Uint16 len);
    Uint16 opcode;
    Uint16 lAddr;
    Uint16 hAddr;
    OTA_SERVICE_ADDR addr;
}OTA_SERVICE_RX_APP;

typedef struct
{
    FIND_HEADER     pfFindHeader;
    CHECK_LEN       pfCheckLen;
    CHECK_SUM       pfCheckSum;
    UPDATE_FRAME    pfUpdateFrame;
    UPDATE_HEAD_POS pfUpdateHeadPos;
    void(*pfRxAdapt)(SCIRXQUE* q);
    /* data */
    OTA_SERVICE_RX_APP* pOtaServiceRxApp;
    Uint16          rxFrameLen;
    Uint16          headerLen;
    Uint16          tailLen;
    Uint16          extraLen;

}OTA_SERVICE_RX_ADAPT;


typedef enum
{
    OTA_UD_H_ADDR   = 0,
    OTA_UD_F_DATA   = 1,
    OTA_RX_S_CMD    = 2,
    OTA_RX_E_CMD    = 3,
    OTA_RX_RFU1     = 4,
    OTA_RX_RFU2     = 5,
    OTA_RX_RFU3     = 6,
    OTA_RX_RFU4     = 7,
}E_OTA_OPCODE;

typedef enum
{
    OTA_SERVICE_IDLE,
    OTA_SERVICE_RX_START_CMD,
    OTA_SERVICE_START,
    OTA_SERVICE_RUNNING,
    OTA_SERVICE_RX_FINISHED,
    OTA_SERVICE_END,
    OTA_SERVICE_FAULT,
}E_OTA_STATUS;

typedef struct
{
    E_OTA_STATUS        currentStatus;

#if (OTA_TEST == INCLUDE_FEATURE)
    OTA_TEST_VERIFY*    pTestData;
#endif /* #if (OTA_TEST == INCLUDE_FEATURE) */
/* Function poniters define here*/
    ERASE_FLASH_A       pfEraseFlashA;       
    ERASE_FLASH_B       pfEraseFlashB;       
    ERASE_FLASH_G       pfEraseFlashG;    
    IS_OTA_ALLOWED      pfIsOtaAllowed;
    FLASH_LINE_DATA     pfFlashLineData;
    GET_CURRENT_STATUS  pfGetCurrentStatus;
    SYSTEM_REBOOT       pfSystemReboot;

    READ_CUR_VER_NUM    pfReadCurVerNum;
    READ_NEW_VER_NUM    pfReadNewVerNum;

    Uint16*             pImageBitMap;
    Uint16              imageTotalLines;
    Uint16              currentLineNum;
    Uint16              rxLineNum;
    Uint16              lastLineNum;

    Uint32              areaSectorB;
    Uint32              areaSectorA;
    Uint32              areaSectorG;

    OTA_SERVICE_RX_ADAPT    *pOtaServiceRxAdapt;
    OTA_SERVICE_LOG_CNT     *pOtaSeviceLogCnt;
}OTA_SERVICE_ADT;

void OTA_SERVICE_PROCESS_RX_DATA_ADAPT(SCIRXQUE* q);

extern OTA_SERVICE_ADT  gOtaServiceAdt;
extern OTA_SERVICE_ADT* pgOtaServiceAdt;
#define PTR_OTA_SERVICE_ADT (&gOtaServiceAdt)
#define PTR_OTA_SERVICE_ADT_RX_ADAPT (gOtaServiceAdt.pOtaServiceRxAdapt)
#define PTR_OTA_SERVICE_ADT_RX_APP (gOtaServiceAdt.pOtaServiceRxAdapt->pOtaServiceRxApp)
#define PTR_OTA_SERVICE_ADT_LOG_CNT (gOtaServiceAdt.pOtaSeviceLogCnt)

static inline void OTA_SERVICE_INTERRUPT_DISABLE(void)
{
    DINT;
    DRTM;
}

static inline void OTA_SERVICE_INTERRUPT_ENABLE(void)
{
    EINT;
    ERTM;
}
#endif /* OTA_SERVICE_H */
