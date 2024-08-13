#ifndef __ALGO_H__
#define __ALGO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

void init();
void loop();
void dataModeWrite();
void sensorSetModeWrite();
void sensorSettingInit();
void sensorSetting(uint8_t adcData1, uint8_t adcData2);

#ifdef __cplusplus
}
#endif

#endif