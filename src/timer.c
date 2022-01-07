#include "timer.h"

void TIMER0_Init(void)
{
    sei();
    TCCR0A = 0x00;                 // normal mode
    TCCR0B |= (1 << 0) | (1 << 2); // Prescaler 1024
    TIMSK0 |= (1 << 0);            // timer overflow interrupt enable
    _delay_us(100);
}
