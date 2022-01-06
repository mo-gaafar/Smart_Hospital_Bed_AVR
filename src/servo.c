#include "DIO.h"
#include <avr/io.h>

#define SERVO_PRT 'C'//D
#define SERVO_PIN 4 //3
#define SERVO_TIMER

// Timer 2 Fast PWM
void SERVO_init(void)
{
    DIO_SetPinDirection(SERVO_PRT, SERVO_PIN, OUTPUT);
    // TODO: initialize timer2 in phase correct PWM mode
    // TCCR2B |= 0b01
}

/*
0 - STOP
1 - LEFT
2 - RIGHT
*/
void SERVO_on(unsigned char cmd)
{
    switch (cmd)
    {
    case 0:
        /* code */
        break;

    case 1:
        /* code */
        break;

    case 2:
        /* code */
        break;

    default:
        break;
    }
}