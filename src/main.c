#include <avr/io.h>
#include <util/delay.h>
#include "pushbuttons.h"
#include "lcd.h"

unsigned char key;

void sleep1(void)
{
  lcd_sendstring("sleeping...");
  _delay_ms(200);
  LCD_SendCommand(1);
  lcd_sendstring("body temp:37");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:roomtemp");
  lcd_sendstring("2:home ");
}
void sleep2(void)
{
  LCD_SendCommand(1);
  lcd_sendstring("room temp:27");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:weight");
  lcd_sendstring(" 2:home ");
}
void sleep3(void)
{
  LCD_SendCommand(1);
  lcd_sendstring("weight:60");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:sleeptime");
  lcd_sendstring("2:home ");
}
void sleep4(void)
{
  LCD_SendCommand(1);
  lcd_sendstring("sleepingtime:8hours");
  lcd_setcursor(1, 0);
  lcd_sendstring("2:home ");
}

// temporary wrapper function for keypad/pushbuttons

unsigned char choose(void)
{
  do
  {
    key = PUSHBUTTONS_read();

  } while (key == 0xff);
  return key;
}

int main(void)
{
  //_delay_ms(200);
  unsigned char mode = 5;
  LCD_Init();
  PUSHBUTTONS_init();

  lcd_sendstring("hello");
  _delay_ms(200);
  LCD_SendCommand(1);
  while (mode == 5)
  {
    LCD_SendCommand(1);
    lcd_sendstring("1:for sleep mode");
    lcd_setcursor(1, 0);
    lcd_sendstring("2:for sit mode");
    mode = choose();
    LCD_SendCommand(1);
    if (mode == 1)
    {
      sleep1();
      mode = choose();
      if (mode == 1)
      {
        sleep2();
        mode = choose();

        if (mode == 1)
        {
          sleep3();
          mode = choose();
          if (mode == 1)
          {
            sleep4();
            mode = choose();
            if (mode == 2)
            {
              mode = 5;
            }
          }
          else if (mode == 2)
          {
            mode = 5;
          }
        }

        else if (mode == 2)
        {

          mode = 5;
        }
      }

      else if (mode == 2)
      {
        mode = 5;
      }
    }
    else if (mode == 2)
    { // last if condition
      mode = 5;
    }
  }
}
