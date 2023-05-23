/*
 * app_main.c
 *
 *  Created on: May 23, 2023
 *      Author: egoerlich
 */
#include "main.h"

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
static const int arr_len = sizeof(LED) /sizeof(LED[0]);

void led_set_all(GPIO_PinState state);
void led_set(int led, GPIO_PinState state);


void setup(){
	led_set_all(GPIO_PIN_RESET);
}

int i = -1;
int dir = 1;
void loop(){
	led_set(i,GPIO_PIN_RESET);
	i = (i + dir) % arr_len;
	if(i == 0) dir =1;
	if(i == 9) dir =-1;

	led_set(i,GPIO_PIN_SET);
	HAL_Delay(800);
}

void led_set_all(GPIO_PinState state){

	for(int i = 0; i < arr_len; i++ )
		led_set(i,state);
}

void led_set(int led, GPIO_PinState state)
{
	int led_inrange = led % arr_len;
	if(led_inrange >=0)
		HAL_GPIO_WritePin(LED[led_inrange].port, LED[led_inrange].pin, state);
}
