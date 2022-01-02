#include"ADC.h"
#include"STD_TYPES.h"
#include "avr/io.h"
#include"BIT_MATH.h"




void ADC_Init (void)
{
	// ADC Enable
	SET_BIT(ADCSRA,7);

	// Prescaler Configuration as 128
	SET_BIT(ADCSRA,2);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,0);


	// Referance Voltage as AVCC with external capacitor
	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);

	// ADC Data Rgith Adjustment
	CLR_BIT(ADMUX,5);
}

/*
MUX4...0        (+ Differential Input)      ( – Differential Input)      Gain

01001                  ADC1                         ADC0                10x

01011                  ADC1                         ADC0                200x

*/
u16 ADC_Read (u8 channel)
{
	// ADC Channel Selection
	
	ADMUX &=0b11100000;
	ADMUX |=(channel &0b00011111);

	// Start Single Convertion
	SET_BIT(ADCSRA,6);

	//wait for the conversion
	while (ADCSRA & (1 << 6));

	return ADC;
}
