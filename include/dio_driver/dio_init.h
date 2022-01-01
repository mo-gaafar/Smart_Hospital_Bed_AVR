#ifndef _DIO_INT_H
#define _DIO_INT_H

/* Port Defines */
#define PORT_B    1
#define PORT_C    2
#define PORT_D    3

/* PIN Defines */
#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0
#define FULL_OUTPUT 0xff

/* IO Pins */
void DIO_SetPinValue(u8 port , u8 PinId, u8 PinVal);

u8 DIO_GetPinValue(u8 port, u8 PinId);

void DIO_SetPinDirection (u8 port, u8 PinId, u8 PinDir);

/* IO Ports */
void DIO_SetPortDirection (u8 Port, u8 PortDir);

void DIO_SetPortValue     (u8 Port, u8 PortVal);

#endif
