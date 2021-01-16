#ifndef PF_DATA_STRUCT_H_
#define PF_DATA_STRUCT_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File


typedef struct _PF_RING_BUFFER
{
    Uint16 front;
    Uint16 rear;
    Uint16 bufferLen;
    Uint16* buffer;
}PF_RING_BUFFER;


typedef struct _PF_HIGH_LOW_BYTE{
	Uint16 h : 8;
	Uint16 l: 8;
}PF_HIGH_LOW_BYTE;

typedef union _PF_UION_2BYTES{
	PF_HIGH_LOW_BYTE datahl;
	Uint16 value;
}PF_UION_2BYTES;
/******************************************************************************/
/******************************************************************************/
/***************************Rx Packet Format***********************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

typedef struct _PF_RX_PACKET_VERIFY
{
	Uint16* verify;
	Uint16 	verifyLen;
}PF_RX_PACKET_VERIFY;

typedef struct _PF_RX_PACKET_PROTOCAL
{
	Uint16*	head;
    Uint16* data;
	Uint16*	verify;
	Uint16*	tail;
}PF_RX_PACKET_PROTOCAL;
/******************************************************************************/
/******************************************************************************/
/***************************Tx Packet Format***********************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


#endif
