#ifndef _RELAY_H
#define _RELAY_H

#include <DIO.h>
#include <util/delay.h>

#define HEATER_PRT 'B'
#define HEATER_PIN 5

#define LAMP_PRT 'B'
#define LAMP_PIN 4

#define Buzzer_prt 'C'
#define Buzzer_PIN 5

// SET PIN DIRECTIONS
void RELAY_Init(void);

/*
0 HEATER OFF
1 HEATER ON
*/
void RELAY_Heater(unsigned char state);

/*
0 LAMP OFF
1 LAMP ON
*/
void RELAY_Lamp(unsigned char state);

// Failure.. dont use with interrupt timer service
void RELAY_Lamp_Alert(unsigned char timesec);

void buzzer_init(void);
void Buzzer_on(void);
#endif