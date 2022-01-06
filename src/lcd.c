#include "lcd.h"
#include "STD_TYPES.h"

#include "avr/io.h"
#include "util/delay.h"
#include "dio_init.h"

#define lcd_Clear 0x01           /* replace all characters with ASCII 'space'                       */
#define lcd_Home 0x02            /* return cursor to first position on first line                   */
#define lcd_EntryMode 0x06       // shift cursor from left to right on read/write
#define lcd_DisplayOff 0x08      // turn display off
#define lcd_DisplayOn 0x0C       // display on, cursor off, don't blink character
#define lcd_FunctionReset 0x30   // reset the LCD
#define lcd_FunctionSet8bit 0x38 // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor 0x80       // set cursor position
#define lcd_4bit_init1 0x33
#define lcd_4bit_init2 0x32
#define lcd_4bit_init3 0x28
// defines data pins
#define LCD_DPRT PORT_B
#define LCD_CPRT PORT_C
// defines controls pins
#define LCD_RS 0                   // LCD RS
#define LCD_RW 1                   // LCD RW
#define LCD_EN 2                   // LCD EN
static void LCD_LatchSignal(void); // to make enable 1 and return to 0

void LCD_Init(void)
{
#if LCD_MODE == LCD_8BIT_MODE
    DIO_SetPortDirection(LCD_DPRT, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
    LCD_SendCommand(0x38);
    LCD_SendCommand(0x0E);
    LCD_SendCommand(0x01);
    _delay_ms(2);
#elif LCD_MODE == LCD_4BIT_MODE
    DIO_SetPinDirection(LCD_DPRT, 4, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 5, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 6, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 7, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, LCD_RW, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, LCD_EN, OUTPUT);
    LCD_SendCommand(0x33);
    LCD_SendCommand(0x32);
    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0E);
    LCD_SendCommand(0x01);
    _delay_ms(2);
#else
#error Please Select The Correct Mode of LCD
#endif
}
void LCD_SendCommand(unsigned char Command)
{
#if LCD_MODE == LCD_8BIT_MODE
    DIO_SetPortValue(LCD_DPRT, Command);

    DIO_SetPinValue(LCD_CPRT, LCD_RS, 0);
    DIO_SetPinValue(LCD_CPRT, LCD_RW, 0);
    LCD_LatchSignal();

#elif LCD_MODE == LCD_4BIT_MODE
    // TODO: fix this so that we can put non consecutive combinations of ports
    DIO_SetPinValue(LCD_CPRT, LCD_RS, 0);
    DIO_SetPinValue(LCD_CPRT, LCD_RW, 0);
    // PORTD = (PORTD & 0x0f) | (Command & 0xf0);
    LCD_LatchSignal();
    // PORTD = (PORTD & 0x0f) | (Command << 4);
    LCD_LatchSignal();
#else
#error Please Select The Correct Mode of LCD
#endif
}

void LCD_SendData(unsigned char Data)
{
#if LCD_MODE == LCD_8BIT_MODE
    DIO_SetPortValue(LCD_DPRT, Data);

    DIO_SetPinValue(LCD_CPRT, LCD_RS, 1);
    DIO_SetPinValue(LCD_CPRT, LCD_RW, 0);
    LCD_LatchSignal();
#elif LCD_MODE == LCD_4BIT_MODE
    DIO_SetPinValue(LCD_CPRT, LCD_RS, 1);
    DIO_SetPinValue(LCD_CPRT, LCD_RW, 0);
    // TODO: fix this so that we can put non consecutive combinations of ports
    // DIO_SetPortValue(LCD_DPRT, (DIO_ReadPort(LCD_DPRT) & 0x0f) | (Data & 0xf0));
    // PORTD = (PORTD & 0x0f) | (Data & 0xf0);
    LCD_LatchSignal();
    // DIO_SetPortValue(LCD_DPRT, (DIO_ReadPort(LCD_DPRT) & 0x0f) | (Data << 4));
    //  PORTD = (PORTD & 0x0f) | (Data << 4);
    LCD_LatchSignal();

#else
#error Please Select The Correct Mode of LCD
#endif
}
void lcd_setcursor(unsigned char x, unsigned char y)
{

    unsigned char address = 0;
    if (x == 0)
    {
        address = y;
        LCD_SendCommand(address + 128);
    }
    else
    {
        address = 0x40 + y;
        LCD_SendCommand(address + 128);
    }
}
void lcd_sendstring(const char *Str)
{
    unsigned char i = 0;
    while (!(Str[i] == '\0'))
    {
        LCD_SendData(Str[i]);
        i++;
    }
}
void lcd_sendSpecialCharachter(unsigned char *arr, unsigned char patternno, unsigned char x, unsigned char y)
{

    unsigned char cgramaddress = 0;
    unsigned char i;
    cgramaddress = 8 * patternno;
    LCD_SendCommand(cgramaddress + 64);
    for (i = 0; i < 8; i++)
    {
        LCD_SendData(arr[i]);
    }
    lcd_setcursor(x, y);
    LCD_SendData(patternno);
}

static void LCD_LatchSignal(void)
{
    DIO_SetPinValue(LCD_CPRT, LCD_EN, 1);
    _delay_us(1);
    DIO_SetPinValue(LCD_CPRT, LCD_EN, 0);
    _delay_us(100);
}
