/*
 * app_main.c
 *
 *  Created on: 25 maj 2023
 *      Author: egoerlich
 */


#include "main.h"
#include "usart.h"
#include <string.h>

void setup(){

}

void loop(){
	  const char received[] = "Odebrano:";
	  const char newline[] = "\r\n";
	  uint8_t value;
	  HAL_UART_Receive(&huart2, &value, 1, HAL_MAX_DELAY);
 	  //printf("Odebrano: %c\n", value);
	  HAL_UART_Transmit(&huart2, (const uint8_t*)received, strlen(received), HAL_MAX_DELAY);
	  HAL_UART_Transmit(&huart2, &value, 1, HAL_MAX_DELAY);
	  HAL_UART_Transmit(&huart2, (const uint8_t*)newline, strlen(newline), HAL_MAX_DELAY);
}
