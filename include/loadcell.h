#ifndef _LOADCELL_H
#define _LOADCELL_H

#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "DIO.h"

void LOADCELL_Init(void);
float LOACELL_ReadWeight(void);

#endif