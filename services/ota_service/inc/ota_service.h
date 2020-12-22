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
