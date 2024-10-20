/*
 * Module: Ultrasonic Driver
 *
 * File Name: Ultrasonic.h
 *
 * Description: Header file for the AVR Ultrasonic driver
 *
 * Author: Omar Sherif
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "std_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * Initialize the ICU driver and set up the necessary configuration for the ultrasonic sensor.
 */
void Ultrasonic_init(void);

/*
 * Description:
 * Send a trigger pulse to the ultrasonic sensor.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * Send a trigger pulse using Ultrasonic_Trigger function and calculate the distance
 * based on the pulse width using the ICU driver.
 *
 * Return:
 * The measured distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * Callback function called by the ICU driver when an edge is detected.
 * It calculates the high time (pulse width) of the echo signal.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H */
