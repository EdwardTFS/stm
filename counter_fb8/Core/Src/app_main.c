/*
 * app_main.c
 *
 *  Created on: May 30, 2023
 *      Author: egoerlich
 */

#include <tim.h>
#include <math.h>

float calc_pwm(float val)
{
    const float k = 0.13f;
    const float x0 = 70.0f;
    return 1000.0f / (1.0f + exp(-k * (val - x0)));
}

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

	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

static int counter = 0;
void loop(){
	float r = 50 * (1.0f + sin(counter / 100.0f));
	float g = 50 * (1.0f + sin(1.5f * counter / 100.0f));
	float b = 50 * (1.0f + sin(2.0f * counter / 100.0f));
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, calc_pwm(r)); //PA0 //red
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, calc_pwm(g)); //PA1 //green
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, calc_pwm(b)); //PB10 //blue

	HAL_Delay(5);
	counter++;
}
