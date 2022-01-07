#ifndef _SERVO_H
#define _SERVO_H

#include "DIO.h"
#include <avr/io.h>
#include <avr/delay.h>

void SERVO_init(void);
void SERVO_on(unsigned char cmd);
void SERVO_off(void);

#endif