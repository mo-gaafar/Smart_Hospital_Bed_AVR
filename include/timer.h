#ifndef _TIMER_H
#define _TIMER_H

#include <DIO.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/* TIMER0, INTERRUPT FLAG EACH 16MS
NORMAL MODE, OVERFLOW INTERRUPT
--
reminder: enable interrupt sreg in main
ISR(TIMER0_OVF_vect)
*/
void TIMER0_Init(void);

#endif