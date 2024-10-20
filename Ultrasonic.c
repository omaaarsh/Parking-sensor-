/*
 * Module: Ultrasonic Driver
 *
 * File Name: Ultrasonic.c
 *
 * Description: Source file for the AVR Ultrasonic with icu driver for (back sensor)
 *
 * Author: Omar Sherif
 */

#include "icu.h"
#include "gpio.h"
#include <util/delay.h>
#include "ultrasonic.h"

/*******************************************************************************
 *                      Definitions                                            *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT    PORTD_ID
#define ULTRASONIC_TRIGGER_PIN     PIN7_ID
#define SOUND_SPEED                34300  /* Sound speed in cm/s */
#define TIMER_TICKS                1      /* Adjust based on Timer configuration */

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

/* Variable to store the time (in microseconds) of the high pulse (echo) */
static volatile uint16 g_high_time = 0;
static volatile uint8 g_edgeCount = 0;
static volatile uint16 distance=0;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Initialize the ICU driver, set the ICU callback function, and configure the trigger pin.
 */
ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
void Ultrasonic_init(void)
{
    /* Set the ICU callback function */
    ICU_setCallBack(Ultrasonic_edgeProcessing);

    /* Configure ICU to detect rising edge first */
    ICU_setEdgeDetectionType(RAISING);

    /* Initialize the ICU driver */
    ICU_init(&ICU_Configurations);

    /* Set the direction of the trigger pin as output */
    GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, PIN_OUTPUT);
}

/*
 * Description:
 * Send a trigger pulse to the ultrasonic sensor by sending a 10us pulse.
 */
void Ultrasonic_Trigger(void)
{
    /* Set the trigger pin high for 10 microseconds */
    GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_HIGH);
    _delay_us(10);
    GPIO_writePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOGIC_LOW);
}

/*
 * Description:
 * Read the distance in centimeters by sending a trigger pulse and calculating
 * the pulse width (high time) using the ICU.
 */
uint16 Ultrasonic_readDistance(void)
{
    /* Trigger the ultrasonic sensor */
    Ultrasonic_Trigger();

    /* Wait until the edge processing is completed */
    while (g_edgeCount < 2);

    /* Calculate the distance in centimeters */
    distance = (uint16)((g_high_time / 117.6)+1);

    /* Reset the edge count for the next measurement */
    g_edgeCount = 0;

    return distance;
}

/*
 * Description:
 * This function is called by the ICU when an edge is detected. It calculates
 * the high time of the echo signal by switching between rising and falling edges.
 */
void Ultrasonic_edgeProcessing(void)
{
    g_edgeCount++;

    if (g_edgeCount == 1)
    {
        /* Start capturing time on the rising edge */
        ICU_clearTimerValue();
        ICU_setEdgeDetectionType(FALLING);
    }
    else if (g_edgeCount == 2)
    {
        /* Capture the high time on the falling edge */
        g_high_time = ICU_getInputCaptureValue();

        /* Set the ICU to detect the next rising edge */
        ICU_setEdgeDetectionType(RAISING);
    }
}
