//인터럽트
//호성제작

#include "interrupt.h"
#include "variable.h"

#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) //타이머 인터럽트 주기:1KHz
{
    if(htim == &htim6)
	{
        gh_senosrVal[0] = HAL_ADC_GetValue(&hadc1);
        gh_senosrVal[1] = HAL_ADC_GetValue(&hadc2);
        gh_sensorResult[0] = (gh_senosrVal[0] < gh_sensorStandardADCVal[0]);
        gh_sensorResult[1] = (gh_senosrVal[1] < gh_sensorStandardADCVal[1]);

        if(gh_transmitMode == 'D')  //데이터 전송 모드
        {
            //변화가 있을때 전송
            if((gh_sensorResultBuff[0] != gh_sensorResult[0]) | (gh_sensorResultBuff[1] != gh_sensorResult[1]))
                dataModeWrite();    //데이터 전송
            gh_sensorResultBuff[0] = gh_sensorResult[0];    //전값 업데이트
            gh_sensorResultBuff[1] = gh_sensorResult[1];
        }
        else if(gh_transmitMode == 'S') //센서세팅
        {
            sensorSetting((uint8_t)gh_senosrVal[0], (uint8_t)gh_senosrVal[1]);  //센서세팅
            sensorSetModeWrite();   //데이터센서전송
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //UART 송신 인터럽트
{
    if (huart->Instance == USART2)
    {
        push(&gh_uartqueue, gh_rx_data);    //수신값 push
        HAL_UART_Receive_IT(&huart2, &gh_rx_data, 1);   //다음 수신인터럽트 활성화
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin); //반짝
    }
}