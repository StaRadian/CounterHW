#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

#include "queue.h"

extern uint8_t gh_rx_data;
extern uint8_t gh_transmitMode;
extern uint32_t gh_senosrVal[2];
extern uint8_t gh_sensorResult[2];
extern uint8_t gh_sensorResultBuff[2];
extern uint32_t gh_sensorStandardADCVal[2];
extern quint8_t gh_uartqueue;

#ifdef __cplusplus
}
#endif

#endif