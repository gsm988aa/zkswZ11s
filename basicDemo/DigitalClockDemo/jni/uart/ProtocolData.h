/*
 * ProtocolData.h
 *
 *  Created on: Sep 7, 2017
 *      Author: guoxs
 */

#ifndef _UART_PROTOCOL_DATA_H_
#define _UART_PROTOCOL_DATA_H_

#include <string>
#include "CommDef.h"

/******************** CmdID ***********************/
#define CMDID_TEST_VALUE					0x1
/**************************************************/

typedef struct {
	BYTE hour;
	BYTE min;
	BYTE sec;
} SProtocolData;

#endif /* _UART_PROTOCOL_DATA_H_ */
