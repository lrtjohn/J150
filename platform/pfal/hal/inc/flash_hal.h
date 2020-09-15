#ifndef PF_FLASH_HAL_H_
#define PF_FLASH_HAL_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "prod.h"
#include "Flash2833x_API_Library.h"
#include <stdlib.h>
void FlashAPI_Init(void);
Uint16 Flash_RD(Uint32 addr, Uint16 *buffer, Uint16 leng);

Uint16 Flash_WR(Uint32 addr, Uint16 *buffer, Uint16 leng);

#endif

