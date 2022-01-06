#ifndef _PUSHBUTTONS_H
#define _PUSHBUTTONS_H

// PIN DEFINITIONS
#define PUSHBUTTON_PRT PORT_B
#define PUSHBUTTON_PIN_UP 6
#define PUSHBUTTON_PIN_DN 5
#define PUSHBUTTON_PIN_LEFT 4
#define PUSHBUTTON_PIN_RIGHT 2

#define DEBOUNCE_DELAY_MS 20
#define KEYPAD_NO_PRESSED_KEY 0xff
void PUSHBUTTONS_init(void);

unsigned char PUSHBUTTONS_read(void);

#endif