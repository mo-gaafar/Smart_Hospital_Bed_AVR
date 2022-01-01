#ifndef _DIO_REG_H
#define _DIO_REG_H



/* Group B Registers */
#define PORTB_Register  *((volatile u8*)0x25)
#define DDRB_Register   *((volatile u8*)0x24)
#define PINB_Register   *((volatile u8*)0x23)

/* Group C Registers */
#define PORTC_Register  *((volatile u8*)0x28)
#define DDRC_Register   *((volatile u8*)0x27)
#define PINC_Register   *((volatile u8*)0x26)

/* Group D Registers */
#define PORTD_Register  *((volatile u8*)0x2B)
#define DDRD_Register   *((volatile u8*)0x2A)
#define PIND_Register   *((volatile u8*)0x29)


#endif
