#include "relay.h"

// PORTS DEFINED IN HEADER FILE

void RELAY_Init(void)
{
    DIO_SetPinDirection(HEATER_PRT, HEATER_PIN, OUTPUT);
    DIO_SetPinDirection(LAMP_PRT, LAMP_PIN, OUTPUT);
}

void RELAY_Heater(unsigned char state)
{
    if (state == 1)
    {
        DIO_WritePin(HEATER_PRT, HEATER_PIN, 1);
    }
    else if (state == 0)
    {
        DIO_WritePin(HEATER_PRT, HEATER_PIN, 0);
    }
}

void RELAY_Lamp(unsigned char state)
{

    if (state == 1)
    {
        DIO_WritePin(LAMP_PRT, LAMP_PIN, 1);
    }
    else if (state == 0)
    {
        DIO_WritePin(LAMP_PRT, LAMP_PIN, 0);
    }
}

void RELAY_Lamp_Alert(unsigned char timesec)
{
    unsigned char state = 0;
    for (unsigned char i = 0; i < timesec; i++)
    {
        _delay_ms(1000);
        RELAY_Lamp(state);
        state = ~state; // toggle state
    }
}
void buzzer_init(void)
{
    DIO_SetPinDirection(Buzzer_prt, Buzzer_PIN, 1);
}
void BUZZER_Pulse_ms(unsigned short ms)
{
    DIO_WritePin(Buzzer_prt, Buzzer_PIN, 1);
    _delay_ms(ms);
    DIO_WritePin(Buzzer_prt, Buzzer_PIN, 0);
}