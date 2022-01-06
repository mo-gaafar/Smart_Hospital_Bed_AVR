#include <avr/io.h>
#include <util/delay.h>
#include "DIO.h"
#include "pushbuttons.h"

unsigned char PUSHBUTTON_PINS[4] = {PUSHBUTTON_PIN_UP, PUSHBUTTON_PIN_DN, PUSHBUTTON_PIN_LEFT, PUSHBUTTON_PIN_RIGHT};

// Setting pin directions
void PUSHBUTTONS_init(void)
{
    for (unsigned char i = 0; i < 4; i++)
    {
        // Setting as input
        DIO_SetPinDirection(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i], INPUT);
        // Setting input pins as pullup
        DIO_WritePin(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i], 1);
    }
}

/*0 BUTTONS RELEASED
1 BUTTON UP
2 BUTTON DOWN
3 BUTTON LEFT
4 BUTTON RIGHT
*/
unsigned char PUSHBUTTONS_read(void)
{
    unsigned char pressedkey=KEYPAD_NO_PRESSED_KEY;
    unsigned char i = 0;

    unsigned char buttonState = 1;

    for (i = 0; i < 4; i++)
    {
        // TODO:if pullup, dont forget to invert inputs
        buttonState = DIO_ReadPin(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i]);
        // if the button is held in the same state within debounce time, return value
        if (buttonState == 0)
        {
            _delay_ms(DEBOUNCE_DELAY_MS);
            buttonState = DIO_ReadPin(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i]);
            if (buttonState == 0)
            {
                pressedkey=(i+1+'0');
                return pressedkey;
            }
        }
    }
    return pressedkey; // if reaches here without being returned, no key is pressed
}

// // enter index as defined in PUSHBUTTON_PINS
// unsigned char PUSHBUTTONS_debounce(unsigned char state, unsigned char button_index)
// {
//     unsigned char stateNow = DIO_GetPinValue(PUSHBUTTON_PRT, PUSHBUTTON_PINS[button_index]);
//     if (state != stateNow)
//     {
//         _delay_ms(DEBOUNCE_DELAY_MS);
//         stateNow = DIO_GetPinValue(PUSHBUTTON_PRT, PUSHBUTTON_PINS[button_index]);
//     }
//     return stateNow;
// }