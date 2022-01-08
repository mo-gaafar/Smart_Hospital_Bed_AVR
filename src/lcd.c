

#include "LCD.h"

#include "DIO.h"
#include "avr/io.h"
#include "util/delay.h"

#define LCD_DPRT 'D' // LCD DATA PORT
#define LCD_CPRT 'D' // LCD COMMANDS PORT
#define LCD_RS 2     // LCD RS
#define LCD_RW 1     // LCD RW
#define LCD_EN 0     // LCD EN

static void LCD_LatchSignal(void);

void LCD_Init()
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
    /// TODO:
    DIO_SetPinDirection(LCD_DPRT, 4, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 5, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 6, OUTPUT);
    DIO_SetPinDirection(LCD_DPRT, 7, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_RS, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_RW, OUTPUT);
    DIO_SetPinDirection(LCD_CPRT, LCD_EN, OUTPUT);
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
    DIO_WritePort(LCD_DPRT, Command);
    DIO_WritePin(LCD_CPRT, LCD_RS, 0);
    DIO_WritePin(LCD_CPRT, LCD_RW, 0);
    LCD_LatchSignal();
#elif LCD_MODE == LCD_4BIT_MODE
    /// TODO:
    DIO_WritePin(LCD_CPRT, LCD_RS, 0);
    DIO_WritePin(LCD_CPRT, LCD_RW, 0);
    PORTD = (PORTD & 0x0f) | (Command & 0xf0);
    LCD_LatchSignal();
    PORTD = (PORTD & 0x0f) | (Command << 4);
    LCD_LatchSignal();

#else
#error Please Select The Correct Mode of LCD
#endif
}

void LCD_SendData(unsigned char Data)
{
#if LCD_MODE == LCD_8BIT_MODE
    DIO_WritePort(LCD_DPRT, Data);

    DIO_WritePin(LCD_CPRT, LCD_RS, 1);
    DIO_WritePin(LCD_CPRT, LCD_RW, 0);
    LCD_LatchSignal();
#elif LCD_MODE == LCD_4BIT_MODE
    DIO_WritePin(LCD_CPRT, LCD_RS, 1);
    DIO_WritePin(LCD_CPRT, LCD_RW, 0);

    DIO_WritePort(LCD_DPRT, (DIO_ReadPort(LCD_DPRT) & 0x0f) | (Data & 0xf0));
    // PORTD=(PORTD & 0x0f)|(Data&0xf0);
    LCD_LatchSignal();
    DIO_WritePort(LCD_DPRT, (DIO_ReadPort(LCD_DPRT) & 0x0f) | (Data << 4));
    // PORTD=(PORTD&0x0f)|(Data<<4);
    LCD_LatchSignal();

#else
#error Please Select The Correct Mode of LCD
#endif
}

void lcd_setcursor(unsigned char x, unsigned char y)
{
    /// TODO:
    char address = 0;
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
    /// TODO:
    int i = 0;
    while (!(Str[i] == '\0'))
    {
        LCD_SendData(Str[i]);
        i++;
    }
}
void send_specialcharachter(unsigned char *arr, char patternno, char x, char y)
{

    char cgramaddress = 0;
    int i;
    cgramaddress = 8 * patternno;
    LCD_SendCommand(cgramaddress + 64);
    for (i = 0; i < 8; i++)
    {
        LCD_SendData(arr[i]);
    }
    lcd_setcursor(x, y);
    LCD_SendData(patternno);
}
void lcd_send_number(unsigned char numb){
  if(numb>=100){
    unsigned char first=numb/100;
    LCD_SendData(first+'0');
    unsigned char second=(numb/10)%10;
    LCD_SendData(second +'0');
    unsigned char third=numb%10;
    LCD_SendData(third +'0');
  

  }
  else if(numb==0||numb<10){
      unsigned char first=numb;
    LCD_SendData(first+'0');

  }
  else{
unsigned char first=numb/10;
LCD_SendData(first+'0');
unsigned char second=numb%10;
LCD_SendData(second+'0');}

}

static void LCD_LatchSignal(void)
{
    DIO_WritePin(LCD_CPRT, LCD_EN, 1);
    _delay_us(1);
    DIO_WritePin(LCD_CPRT, LCD_EN, 0);
    _delay_us(100);
}