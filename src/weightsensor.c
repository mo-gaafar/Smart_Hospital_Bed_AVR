#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "DIO.h"

#define OCCUPANCY_THRESHOLD_V 0.1
#define LOADCELL_PRT 'C'
#define LOADCELL_ADCp 6 //0
#define LOADCELL_ADCn 5//1
#define LOADCELL_ADMUX 0b01001

// Sets analog port direction, doesnt init adc
void LOADCELL_init(void)
{
    DIO_SetPinDirection(LOADCELL_PRT, LOADCELL_ADCp, INPUT);
    DIO_SetPinDirection(LOADCELL_PRT, LOADCELL_ADCn, INPUT);
}

// UNCALIBRATED
float LOADCELL_readweight(void)
{

    unsigned short binary = ADC_Read(LOADCELL_ADMUX);
    float weight = binary;
    // TODO:calibrate weight sensing equation
    return weight;
}
