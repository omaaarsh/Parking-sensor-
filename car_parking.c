/*
 * Module: Ultrasonic Sensor System
 *
 * File Name: main.c
 *
 * Description: Main file for the Ultrasonic distance measurement system.
 *              Controls LCD, LEDs, and buzzer based on distance.
 *
 * Author: Omar Sherif
 */

#include "lcd.h"
#include "gpio.h"
#include "buzzer.h"
#include "led.h"
#include "avr/io.h"
#include <util/delay.h>
#include "ultrasonic.h"

int main(void)
{

    /* Initialize the LCD, ultrasonic sensor, and LED and buzzer drivers */

	uint16 distance = 0;
    LCD_init();
    Ultrasonic_init();
    LEDS_init();
    Buzzer_init();

    // Enable global interrupts
    SREG |= (1 << 7);
    LCD_displayStringRowColumn(0, 0,"Distance: ");
    while(1)
    {
        /* Get the distance measurement from the ultrasonic sensor */
        distance = Ultrasonic_readDistance();
        /* Display the distance on the LCD */
        LCD_moveCursor(0, 10);
        LCD_intgerToString(distance);
        LCD_displayString(" cm");

        /* Distance Mapping to LED and Buzzer */
        if (distance <= 5)
        {
            /* All LEDs Flashing and Buzzer ON */
        	while(distance < 6){
				Buzzer_on();
				LED_on(LED_RED);
				LED_on(LED_GREEN);
				LED_on(LED_BLUE);
				_delay_ms(200);
	            LED_off(LED_RED);
	            LED_off(LED_GREEN);
	            LED_off(LED_BLUE);
				LCD_moveCursor(1, 6);
				LCD_displayString("Stop!");
				distance = Ultrasonic_readDistance();
		        LCD_moveCursor(0, 10);
		        LCD_intgerToString(distance);
		        LCD_displayString(" cm");
        	}
        	LCD_clearScreen();
        	LCD_displayStringRowColumn(0, 0,"Distance: ");
        }
        else if (distance <= 10)
        {
            /* All LEDs ON, Buzzer OFF */
            LED_on(LED_RED);
            LED_on(LED_GREEN);
            LED_on(LED_BLUE);
            Buzzer_off();
        }
        else if (distance <= 15)
        {
            /* Red and Green LEDs ON, Blue LED OFF */
            LED_on(LED_RED);
            LED_on(LED_GREEN);
            LED_off(LED_BLUE);
            Buzzer_off();
        }
        else if (distance <= 20)
        {
            /* Only Red LED ON, others OFF */
            LED_on(LED_RED);
            LED_off(LED_GREEN);
            LED_off(LED_BLUE);
            Buzzer_off();
        }
        else
        {
            /* All LEDs OFF, Buzzer OFF */
            LED_off(LED_RED);
            LED_off(LED_GREEN);
            LED_off(LED_BLUE);
            Buzzer_off();
        }

        /* Small delay to avoid LCD flickering */
        _delay_ms(200);
    }
}
