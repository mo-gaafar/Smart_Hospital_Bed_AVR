#include "loadcell.h"

#define OCCUPANCY_THRESHOLD_V 0.1
#define LOADCELL_PRT 'C'
#define LOADCELL_ADCp 0
#define LOADCELL_ADCn 1
#define LOADCELL_ADMUX 0b00001

// Sets analog port direction, doesnt init adc
void LOADCELL_Init(void)
{
    DIO_SetPinDirection(LOADCELL_PRT, LOADCELL_ADCp, INPUT);
    DIO_SetPinDirection(LOADCELL_PRT, LOADCELL_ADCn, INPUT);
}

// UNCALIBRATED
float LOADCELL_ReadWeight(void)
{

    unsigned short binary = ADC_Read(LOADCELL_ADMUX);
    float weight = binary;
    // TODO:calibrate weight sensing equation
    return weight;
}
