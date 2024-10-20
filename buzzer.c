#include "gpio.h"
#include "buzzer.h"

/* Initialize the buzzer pin as output and turn it off initially */
void Buzzer_init(void)
{
    /* Set the buzzer pin as output */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

    /* Turn off the buzzer */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}

/* Turn on the buzzer */
void Buzzer_on(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

/* Turn off the buzzer */
void Buzzer_off(void)
{
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
