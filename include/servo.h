#ifndef _SERVO_H
#define _SERVO_H

#include "DIO.h"
#include <avr/io.h>
#include <util/delay.h>

void SERVO_Init(void);
void SERVO_On(unsigned char cmd);
void SERVO_Off(void);

#endif