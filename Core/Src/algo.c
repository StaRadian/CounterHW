//알고리즘
//호성제작

#include "algo.h"

#include <string.h>
#include "usart.h"
#include "variable.h"

uint8_t gh_sensorMax[2];
uint8_t gh_sensorMin[2];

void init()//초기화
{
    gh_transmitMode = 0;
    gh_sensorStandardADCVal[0] = 0x27;
    gh_sensorStandardADCVal[1] = 0x27;
    init_queue(&gh_uartqueue);
    HAL_UART_Transmit (&huart2, "START", 5, 10);//실행
}

void loop()//루프문
{
    if (isEmpty(&gh_uartqueue) == 0)
    {
        gh_transmitMode = pop(&gh_uartqueue);
        if(gh_transmitMode == 'H')//하이
        {
            HAL_UART_Transmit (&huart2, "HI", 2, 10);
        }
        else if(gh_transmitMode == 'D') //데이터 전송
        {
            gh_sensorResultBuff[0] = gh_sensorResult[0];
            gh_sensorResultBuff[1] = gh_sensorResult[1];
            dataModeWrite();    //데이터 출력
        }
        else if(gh_transmitMode == 'S')//센서 Setting
        {
            sensorSettingInit();    //센서세팅 초기화
        }
    }
    if(gh_sensorResult[0] & gh_sensorResult[1])    //둘다 On일때 반짝
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}

void dataModeWrite()    //데이터 값 전송
{
    char result[3] = "DNN";
    if(gh_sensorResult[0]) result[1] = 'Y';
    if(gh_sensorResult[1]) result[2] = 'Y';
    HAL_UART_Transmit (&huart2, result, 3, 10);
}

void sensorSetModeWrite()   //데이터, 센서값 전송
{
    char result[6] = "S0000";
    result[1] = gh_senosrVal[0]+47;
    result[2] = gh_senosrVal[1]+47;
    result[3] = gh_sensorStandardADCVal[0];
    result[4] = gh_sensorStandardADCVal[1];
    HAL_UART_Transmit (&huart2, result, 5, 10);
}

void sensorSettingInit()
{
    gh_sensorMax[0] = 0;
    gh_sensorMax[1] = 0;
    gh_sensorMin[0] = 62;
    gh_sensorMin[1] = 62;
}

void sensorSetting(uint8_t adcData1, uint8_t adcData2)
{
    if(gh_sensorMax[0] < adcData1)
    {
        gh_sensorMax[0] = adcData1;
    }
    else if(gh_sensorMin[0] > adcData1)
    {
        gh_sensorMin[0] = adcData1;
    }
    if(gh_sensorMax[1] < adcData2)
    {
        gh_sensorMax[1] = adcData2;
    }
    else if(gh_sensorMin[1] > adcData2)
    {
        gh_sensorMin[1] = adcData2;
    }
    gh_sensorStandardADCVal[0] = (gh_sensorMax[0] + gh_sensorMin[0]) / 2;
    gh_sensorStandardADCVal[1] = (gh_sensorMax[1] + gh_sensorMin[1]) / 2;
}