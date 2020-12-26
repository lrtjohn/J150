#include "ota_service.h"


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
    gOtaServiceTestData.aStart = 0;
    gOtaServiceTestData.aLen = 0;
    gOtaServiceTestData.aEnd = 0;

    gOtaServiceTestData.bStart = 0;
    gOtaServiceTestData.bLen = 0;
    gOtaServiceTestData.bEnd = 0;

    gOtaServiceTestData.cStart = 0;
    gOtaServiceTestData.cLen = 0;
    gOtaServiceTestData.cEnd = 0;

    gOtaServiceTestData.dStart = 0;
    gOtaServiceTestData.dLen = 0;
    gOtaServiceTestData.dEnd = 0;

    gOtaServiceTestData.eStart = 0;
    gOtaServiceTestData.eLen = 0;
    gOtaServiceTestData.eEnd = 0;

    gOtaServiceTestData.fStart = 0;
    gOtaServiceTestData.fLen = 0;
    gOtaServiceTestData.fEnd = 0;

    gOtaServiceTestData.gStart = 0;
    gOtaServiceTestData.gLen = 0;
    gOtaServiceTestData.gEnd = 0;

    gOtaServiceTestData.hStart = 0;
    gOtaServiceTestData.hLen = 0;
    gOtaServiceTestData.hEnd = 0;

    gOtaServiceTestData.userBootStart = 0;
    gOtaServiceTestData.userBootLen = 0;
    gOtaServiceTestData.userBootEnd = 0;

    gOtaServiceTestData.userAppAStart = 0;
    gOtaServiceTestData.userAppALen = 0;
    gOtaServiceTestData.userAppAEnd= 0;

    gOtaServiceTestData.userAppBStart = 0;
    gOtaServiceTestData.userAppBLen = 0;
    gOtaServiceTestData.userAppBEnd= 0;

    gOtaServiceTestData.GlobalStart = 0;
    gOtaServiceTestData.GlobalLen = 0;
    gOtaServiceTestData.GlobalEnd= 0;

    gOtaServiceTestData.Delta =0;
}

#endif /* (OTA_TEST == INCLUDE_FEATURE) */
