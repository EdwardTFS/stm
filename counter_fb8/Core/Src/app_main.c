/*
 * app_main.c
 *
 *  Created on: May 30, 2023
 *      Author: egoerlich
 */

#include <tim.h>

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim6) {
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  }
  if (htim == &htim3) {
      HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim == &htim3) {
    switch (HAL_TIM_GetActiveChannel(&htim3)) {
    case HAL_TIM_ACTIVE_CHANNEL_1:
    	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
      break;
    case HAL_TIM_ACTIVE_CHANNEL_2:
    	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
      break;
    case HAL_TIM_ACTIVE_CHANNEL_3:
    	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
      break;
    default:
      break;
    }
  }
}

void setup(){
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_OC_Start_IT(&htim3, TIM_CHANNEL_3);
}

void loop(){}
