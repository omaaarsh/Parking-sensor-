/******************************************************************************
 *
 * Module: LED Driver
 *
 * File Name: led_driver.c
 *
 * Description: Source file for controlling RGB LEDs based on light intensity
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#include "led.h"
#include "gpio.h"  /* Assuming GPIO functions are defined in gpio.h */
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LEDS_init()
{
    /* Set the pin direction for each LED pin */
    GPIO_setupPinDirection(LED_RED_PORT_ID,LED_RED_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID, PIN_OUTPUT);
    /* Turn off all LEDs */
    LED_off(LED_RED);
    LED_off(LED_GREEN);
    LED_off(LED_BLUE);
}
void LED_on(uint8 id)
{
	#if(LED_MODE==LOGIC_HIGH)
		if(id==LED_RED){
			GPIO_writePin(LED_RED_PORT_ID,LED_RED_PIN_ID,LOGIC_HIGH);
		}
		else if(id==LED_GREEN){
			GPIO_writePin(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID,LOGIC_HIGH);
		}
		else if(id==LED_BLUE){
			GPIO_writePin(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID,LOGIC_HIGH);
		}
	#elif(LED_MODE==LOGIC_LOW)
		if(id==LED_RED){
			GPIO_writePin(LED_RED_PORT_ID,LED_RED_PIN_ID,LOGIC_LOW);
		}
		else if(id==LED_GREEN){
			GPIO_writePin(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID,LOGIC_LOW);
		}
		else if(id==LED_BLUE){
			GPIO_writePin(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID,LOGIC_LOW);
		}
	#endif
}
void LED_off(uint8 id)
{
	#if(LED_MODE==LOGIC_HIGH)
		if(id==LED_RED){
			GPIO_writePin(LED_RED_PORT_ID,LED_RED_PIN_ID,LOGIC_LOW);
		}
		else if(id==LED_GREEN){
			GPIO_writePin(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID,LOGIC_LOW);
		}
		else if(id==LED_BLUE){
			GPIO_writePin(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID,LOGIC_LOW);
		}
	#elif(LED_MODE==LOGIC_LOW)
		if(id==LED_RED){
			GPIO_writePin(LED_RED_PORT_ID,LED_RED_PIN_ID,LOGIC_HIGH);
		}
		else if(id==LED_GREEN){
			PIO_writePin(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID,LOGIC_HIGH);
		}
		else if(id==LED_BLUE){
			GPIO_writePin(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID,LOGIC_HIGH);
		}
	#endif
}

/*
 * Description:
 * This function adjusts the brightness of the LEDs based on the light intensity.
 * It turns on one or more LEDs based on the intensity level.
 */
void LED_adjustBrightness(uint16 light_intensity)
{
    /* Simple logic to control LEDs based on light intensity */
    if (light_intensity >= 0 && light_intensity <= 33) {
        /* Turn on only the red LED for low intensity */
        LED_on(LED_RED);
        LED_off(LED_GREEN);
        LED_off(LED_BLUE);
    }
    else if (light_intensity > 33 && light_intensity <= 66) {
        /* Turn on the red and green LEDs for medium intensity */
        LED_on(LED_RED);
        LED_on(LED_GREEN);
        LED_off(LED_BLUE);
    }
    else if (light_intensity > 66) {
        /* Turn on all LEDs for high intensity */
        LED_on(LED_RED);
        LED_on(LED_GREEN);
        LED_on(LED_BLUE);
    }
    else {
        /* Turn off all LEDs if intensity is invalid */
        LED_off(LED_RED);
        LED_off(LED_GREEN);
        LED_off(LED_BLUE);
    }
}

void LED_flash(uint8 id)
{
    LED_on(id);
    _delay_ms(200);
    LED_off(id);
    _delay_ms(200);
}
