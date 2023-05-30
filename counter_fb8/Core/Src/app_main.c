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
}

void setup(){
	HAL_TIM_Base_Start_IT(&htim6);
}

void loop(){}
