#ifndef OTA_SERVICE_H
#define OTA_SERVICE_H

#include "DSP2833x_Device.h"
#include "prod_defs.h"

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
 * Currently it is a little bit to tell which solution is better.
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
#endif /* OTA_SOLUTION_1 == INCLUDE_FEATURE */

#define DLETA_BETWEEN_A_AND_B           (0)

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
#endif /* OTA_TEST == INCLUDE_FEATURE */

#endif /* OTA_SERVICE_H */
