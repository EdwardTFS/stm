/*
 * app_main.c
 *
 *  Created on: 25 maj 2023
 *      Author: egoerlich
 */


#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>

#define LINE_MAX_LENGTH	80
#define LINE_BUFFER_OVERRUN -1
#define LINE_OK 0

static char line_buffer[LINE_MAX_LENGTH + 1];
static uint32_t line_length;
static const char newline[] = "\r\n";
static const char overrun_message[] = "Przepełnienie\r\n";
static const char unknown_message[] = "Nieznane polecenie\r\n";

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
}pin_t;

static const pin_t LED[] = {
		{ LED0_GPIO_Port, LED0_Pin },
		{ LED1_GPIO_Port, LED1_Pin },
		{ LED2_GPIO_Port, LED2_Pin },
		{ LED3_GPIO_Port, LED3_Pin },
		{ LED4_GPIO_Port, LED4_Pin },
		{ LED5_GPIO_Port, LED5_Pin },
		{ LED6_GPIO_Port, LED6_Pin },
		{ LED7_GPIO_Port, LED7_Pin },
		{ LED8_GPIO_Port, LED8_Pin },
		{ LED9_GPIO_Port, LED9_Pin },
};
static const unsigned int arr_len = sizeof(LED) /sizeof(LED[0]);

int read_line()
{
	uint8_t value;
	line_length = 0;
	while(line_length < LINE_MAX_LENGTH){
		 if(HAL_UART_Receive(&huart2, &value, 1, 1) == HAL_OK){
			 if (value == '\r' || value == '\n') {
				 // odebraliśmy znak końca linii
				 if (line_length > 0) {
					 // jeśli bufor nie jest pusty to dodajemy 0 na końcu linii
					 line_buffer[line_length] = '\0';
					 return LINE_OK;
				 }
			 }
			 line_buffer[line_length++] = value;
		 }
	}
	return LINE_BUFFER_OVERRUN;
}

void led_set(unsigned int led, GPIO_PinState state)
{
	unsigned int led_inrange = led % arr_len;
	HAL_GPIO_WritePin(LED[led_inrange].port, LED[led_inrange].pin, state);
}

void process_command(void){
	if (strcmp(line_buffer, "ON") == 0) {
		led_set(0, GPIO_PIN_SET);
		return;
	}
	if (strcmp(line_buffer, "OFF") == 0) {
		led_set(0, GPIO_PIN_RESET);
				return;
	}
	 HAL_UART_Transmit(&huart2, (const uint8_t*)unknown_message, strlen(unknown_message), HAL_MAX_DELAY);
}

void setup(){

}

void loop(){
	  int read_line_status = read_line();
	  switch(read_line_status){
	  	  case LINE_OK:
	  		  HAL_UART_Transmit(&huart2, (const uint8_t*)line_buffer, strlen(line_buffer), HAL_MAX_DELAY);
	  		  break;
	  	  case LINE_BUFFER_OVERRUN:
	  		  HAL_UART_Transmit(&huart2, (const uint8_t*)overrun_message, strlen(overrun_message), HAL_MAX_DELAY);
	  		  break;
	  }
	  HAL_UART_Transmit(&huart2, (const uint8_t*)newline, strlen(newline), HAL_MAX_DELAY);
	  process_command();
}
