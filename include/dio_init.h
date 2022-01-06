#ifndef _DIO_INT_H
#define _DIO_INT_H

/* Port Defines */
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

/* PIN Defines */
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

/* PIN Directions */
#define INPUT 0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH 1
#define LOW 0
#define FULL_OUTPUT 0xff

/* IO Pins */
void DIO_SetPinValue(unsigned char port, unsigned char PinId, unsigned char PinVal);

unsigned char DIO_GetPinValue(unsigned char port, unsigned char PinId);

void DIO_SetPinDirection(unsigned char port, unsigned char PinId, unsigned char PinDir);

/* IO Ports */
void DIO_SetPortDirection(unsigned char Port, unsigned char PortDir);

void DIO_SetPortValue(unsigned char Port, unsigned char PortVal);

#endif
