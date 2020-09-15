#ifndef RVDT_SERVICE_H_
#define RVDT_SERVICE_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


extern Uint16 *SDB_RVDT_Read_Addr;
Uint16 Get_RVDT_Position(Uint16 *Resolver_read);

#endif
