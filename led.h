/******************************************************************************
 *
 * Module: LED Driver
 *
 * File Name: led_driver.h
 *
 * Description: Header file for controlling RGB LEDs based on light intensity
 *
 * Author: Omar Sherif
 *
 *******************************************************************************/

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LED_RED                1
#define LED_GREEN      		   2
#define LED_BLUE      		   3
#define LED_MODE LOGIC_HIGH /*LOGIC_HIGH for Positive Logic and LOGIC_LOW for Negative Logic.*/
/* Configuration structure for LED pins and logic */
#define LED_RED_PORT_ID                 PORTC_ID
#define LED_RED_PIN_ID                  PIN0_ID
#define LED_GREEN_PORT_ID               PORTC_ID
#define LED_GREEN_PIN_ID                PIN1_ID
#define LED_BLUE_PORT_ID                PORTC_ID
#define LED_BLUE_PIN_ID                 PIN2_ID
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing all LEDs (setting pin directions).
 * It will also turn off all the LEDs.
 */
void LEDS_init(void);

/*
 * Description :
 * Function to turn on the specified LED.
 */
void LED_on(uint8 id);

/*
 * Description :
 * Function to turn off the specified LED.
 */
void LED_off(uint8 id);

#endif /* LED_DRIVER_H_ */
