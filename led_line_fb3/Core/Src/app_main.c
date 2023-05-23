/*
 * app_main.c
 *
 *  Created on: May 23, 2023
 *      Author: egoerlich
 */
#include "main.h"
void setAll(GPIO_PinState state);


void setup(){

}

void loop(){
	setAll(GPIO_PIN_RESET);
	HAL_Delay(800);
	setAll(GPIO_PIN_SET);
	HAL_Delay(200);

}

void setAll(GPIO_PinState state){
	 HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state);
		  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
		  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, state);
		  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, state);
		  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, state);
		  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, state);
		  HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, state);
		  HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, state);
		  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, state);
		  HAL_GPIO_WritePin(LED9_GPIO_Port, LED9_Pin, state);
}
