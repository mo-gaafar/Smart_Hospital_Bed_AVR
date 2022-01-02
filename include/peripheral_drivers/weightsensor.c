#include <avr/io.h>
#include <util/delay.h>
#include "ADC_DRIVER/ADC.c"
#include "dio_driver/dio.c"

#define OCCUPANCY_THRESHOLD_V 0.1
#define LOADCELL_PRT PORT_C
#define LOADCELL_ADCp 0
#define LOADCELL_ADCn 1
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
