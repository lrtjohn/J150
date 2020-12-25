#ifndef OTA_SERVICE_H
#define OTA_SERVICE_H

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

#define USER_BOOTLOADER_START_ADDR
#define USER_BOOTLOADER_SIZE
#define USER_BOOTLOADER_END_ADDR

#define A_APPLICATION_START_ADDR
#define A_APPLICATION_SIZE
#define A_APPLICATION_END_ADDR

#define B_APPLICATION_START_ADDR
#define B_APPLICATION_SIZE
#define B_APPLICATION_END_ADDR

#define GLOBAL_START_ADDR
#define GLOBAL_SIZE
#define GLOBAL_END_ADDR


#endif
