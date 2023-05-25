/*
 * app_main.c
 *
 *  Created on: 25 maj 2023
 *      Author: egoerlich
 */


#include "main.h"
#include "usart.h"
#include <string.h>

#define LINE_MAX_LENGTH	80
#define LINE_BUFFER_OVERRUN -1
#define LINE_INCOMPLETE 0
#define LINE_OK 1

static char line_buffer[LINE_MAX_LENGTH + 1];
static uint32_t line_length;

int line_append(uint8_t value)
{
	if (value == '\r' || value == '\n') {
		// odebraliśmy znak końca linii
		if (line_length > 0) {
			// jeśli bufor nie jest pusty to dodajemy 0 na końcu linii
			line_buffer[line_length] = '\0';
			// przetwarzamy dane
			// zaczynamy zbieranie danych od nowa
			line_length = 0;
			return LINE_OK;
		}

		return LINE_INCOMPLETE;
	}
	else {
		if (line_length >= LINE_MAX_LENGTH) {
			// za dużo danych, usuwamy wszystko co odebraliśmy dotychczas
			line_length = 0;
			return LINE_BUFFER_OVERRUN;
		}
		// dopisujemy wartość do bufora
		line_buffer[line_length++] = value;
		return LINE_INCOMPLETE;
	}
}

void setup(){

}
const char newline[] = "\r\n";
const char overrun_message[] = "Przepełnienie\r\n";
void loop(){
	  uint8_t value;
	  int line_append_status = LINE_INCOMPLETE;
	  while(line_append_status == LINE_INCOMPLETE){
		  if (HAL_UART_Receive(&huart2, &value, 1, 0) == HAL_OK)
			  line_append_status = line_append(value);
	  }
	  switch(line_append_status){
	  	  case LINE_OK:
	  		  HAL_UART_Transmit(&huart2, (const uint8_t*)line_buffer, strlen(line_buffer), HAL_MAX_DELAY);
	  		  break;
	  	  case LINE_BUFFER_OVERRUN:
	  		  HAL_UART_Transmit(&huart2, (const uint8_t*)overrun_message, strlen(overrun_message), HAL_MAX_DELAY);
	  		  break;
	  }
	  HAL_UART_Transmit(&huart2, (const uint8_t*)newline, strlen(newline), HAL_MAX_DELAY);

}
