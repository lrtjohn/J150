#include "ota_service.h"


#if (OTA_TEST == INCLUDE_FEATURE)
OTA_TEST_VERIFY gOtaServiceTestData = 
{
    0
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

#endif /*  */
