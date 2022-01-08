#ifndef _RELAY_H
#define _RELAY_H

#include <DIO.h>
#include <util/delay.h>

#define HEATER_PRT 'B'
#define HEATER_PIN 5

#define LAMP_PRT 'B'
#define LAMP_PIN 4

#define BUZZER_PRT 'C'
#define BUZZER_PIN 5

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
// Initializes buzzer pin
void BUZZER_Init(void);
// Variable ON pulse argument
void BUZZER_Pulse_ms(unsigned short ms);
#endif