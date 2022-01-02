#include <avr/io.h>
#include <util/delay.h>
#include "dio_driver/dio.c"

#define PUSHBUTTON_PRT PORT_D
#define PUSHBUTTON_PIN_UP 6
#define PUSHBUTTON_PIN_DN 5
#define PUSHBUTTON_PIN_LEFT 4
#define PUSHBUTTON_PIN_RIGHT 2

#define DEBOUNCE_DELAY_MS 20

unsigned char PUSHBUTTON_PINS[4] = {PUSHBUTTON_PIN_UP, PUSHBUTTON_PIN_DN, PUSHBUTTON_PIN_LEFT, PUSHBUTTON_PIN_RIGHT};

// Setting pin directions
void PUSHBUTTONS_init(void)
{
    for (unsigned char i = 0; i < 4; i++)
    {
        DIO_SetPinDirection(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i], INPUT);
    }
    // TODO:how to set input ports as pullup?
}

/*0 BUTTONS RELEASED
1 BUTTON UP
2 BUTTON DOWN
3 BUTTON LEFT
4 BUTTON RIGHT
*/

unsigned char PUSHBUTTONS_read(void)
{
    unsigned char i = 0;

    unsigned char buttonState = HIGH;

    for (i = 0; i < 4; i++)
    {
        // TODO:if pullup, dont forget to invert inputs
        buttonState = DIO_GetPinValue(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i]);
        // if the button is held in the same state within debounce time, return value
        if (buttonState == LOW)
        {
            _delay_ms(DEBOUNCE_DELAY_MS);
            buttonState = DIO_GetPinValue(PUSHBUTTON_PRT, PUSHBUTTON_PINS[i]);
            if (buttonState == LOW)
            {
                return i + 1;
            }
        }
    }
    return 0; // if reaches here without being returned, no key is pressed
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