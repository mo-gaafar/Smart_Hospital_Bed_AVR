#include <avr/io.h>
#include <util/delay.h>
#include "pushbuttons.h"
#include "lcd.h"

#define DEBUGMODE 0

#if DEBUGMODE

void main(void)
{
  unsigned char buttonpressed;
  PUSHBUTTONS_init();
  LCD_Init();

  while (1)
  {
  }
}
}

#else

unsigned char key, c, tt; //define variables key for pushed button//c for counting

void sleep1(void) // fframe 1 in sleep mode
{
  lcd_sendstring("sleeping");
  _delay_ms(200);
  LCD_SendCommand(1);
  lcd_sendstring("body temp:37");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:roomtemp");
  lcd_sendstring("2:home ");
}
void sleep2(void)//frame 2 in sleep mode
{
  LCD_SendCommand(1);
  lcd_sendstring("room temp:27");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:weight");
  lcd_sendstring(" 2:home ");
}
void sleep3(void)//frame 3 in sleep mode
{
  LCD_SendCommand(1);
  lcd_sendstring("weight:60");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:sleeptime");
  lcd_sendstring("2:home ");
}
void sleep4(void)//frame 4 in sleep mode
{
  LCD_SendCommand(1);
  lcd_sendstring("sleepingtime:8hours");
  lcd_setcursor(1, 0);
  lcd_sendstring("2:home ");
}
void sit1(void)//frame 1 in sitting mode
{
  LCD_SendCommand(1);
  lcd_sendstring("sitting");
  _delay_ms(200);
  LCD_SendCommand(1);
  lcd_sendstring("options");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:next");
  lcd_sendstring("   2:home ");
}
void sit2(void)//frame 2 in sitting mode
{
  LCD_SendCommand(1);
  lcd_sendstring("heating");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:on");
  lcd_sendstring("  2:off ");
}
void sit3(void)//frame 3 in sitting mode
{
  c = 0;
  LCD_SendCommand(1);
  lcd_sendstring("heater on");
  _delay_ms(200);
  LCD_SendCommand(1);
  lcd_sendstring("heat temp");
  lcd_setcursor(1, 0);
  lcd_sendstring("put temp:");
}
void sit4()//frame 4 in sitting mode
{
  LCD_SendCommand(1);
  lcd_sendstring("lamp enable");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:on");
  lcd_sendstring("  2:off ");
}

unsigned char choose(void)//polling function to w8 user to press key
{
  do
  {

    key = PUSHBUTTONS_read();

  } while (key == 0xff);
  return key;
}
int main(void)
{
  LCD_Init();
  PUSHBUTTONS_init();

  unsigned char mode = 5, Pass = 0, ff = 0;
  lcd_setcursor(0, 4);
  lcd_sendstring("WELCOME!");
  _delay_ms(300);
  LCD_SendCommand(1);
  lcd_setcursor(0, 10);
  lcd_sendstring("For Login");
  lcd_setcursor(1, 3);
  lcd_sendstring("Press :  1");
  key = choose();//wait to check pressed button from the user
  if (key == 1)
  {
    LCD_SendCommand(1);
    while (Pass != 4)  //will be in the loop while the password is not correct 
    {
      ff = 0;
      LCD_SendCommand(1);
      lcd_sendstring("USER : Hassan");
      lcd_setcursor(1, 0);
      lcd_sendstring("PASS : ");
      while (ff != 4)//make password from 4 digit
      {
        key = choose();
        LCD_SendData(key + '0');//to recive correct number in ascii code
        Pass += key;
        ff++;
        if (ff == 4)
          _delay_ms(200);
      }
      ff = 0;
      if (Pass != 4)
      {
        Pass = 0;
        LCD_SendCommand(1);
        lcd_sendstring("wrong pass");
        lcd_setcursor(1, 3);
        lcd_sendstring("try again");
        _delay_ms(200);
      }
    }
    LCD_SendCommand(1);
    mode = 5;
  }

  else  //if user does not want to login so end the program 
  {
    LCD_SendCommand(1);
    mode = 4;
    lcd_sendstring("good bye");
    _delay_ms(200);
    LCD_SendCommand(1);
  }
  // _delay_ms(200);//////////////////////////////////////

  // LCD_Print("hello");
  //_delay_ms(200);
  // LCD_SendCommand(1);
  // _delay_ms(200);

  while (mode == 5) //main function we have 
  {
    LCD_SendCommand(1);                            // make user choose between 2 modes we have in our program
    lcd_sendstring("1:for sleep mode");
    lcd_setcursor(1, 0);
    lcd_sendstring("2:for sit mode");
    mode = choose();
    LCD_SendCommand(1);
    if (mode == 1)  //if user choose sleep mode
    {
      sleep1(); 
      mode = choose();
      if (mode == 1)//user decides to proceed 1
      {
        sleep2();
        mode = choose();

        if (mode == 1) //user decides to proceed 2
        {
          sleep3();
          mode = choose();
          if (mode == 1)//user decides to proceed 3
          {
            sleep4();
            mode = choose();
            if (mode == 2)//user want to return home 3
            {
              mode = 5;
            }
          }
          else if (mode == 2)//user want to return home 2
          {
            mode = 5;
          }
        }

        else if (mode == 2)//user want to return home 1
        {

          mode = 5;
        }
      }

      else if (mode == 2)// if user choose home 0
      {
        mode = 5;
      }
    }
    else if (mode == 2)//user choose sitting mode
    { // last if condition
      sit1();
      mode = choose();
      if (mode == 1)//user want to proceed 1
      {

        sit2();
        mode = choose();
        if (mode == 1)//user want to proceed 2
        {
          LCD_SendCommand(1);
          lcd_sendstring("heater on");
          _delay_ms(200);
          LCD_SendCommand(1);
          sit3();
          while (c != 2)//wait user to set temp then proceed auto to nest step so here user has no option to return home
          {
            key = choose();
            LCD_SendData(key + '0');
            if (c == 0)
            {
              tt = (key + '0') * 10;
            }
            if (c == 1)
            {
              tt += (key + '0');
            }
            c++;
            if (c == 2)
            {
              _delay_ms(100);
            }
          }
          sit4();//proceed to final frame in sitting mode
          mode = choose();
          if (mode == 1)
          {
            LCD_SendCommand(1);
            mode = 5;                 //make mode 5 to return home after outing from this function
            lcd_sendstring("lamp on");
            _delay_ms(200);
          }
          else if (mode == 2)
          {
            LCD_SendCommand(1);
            mode = 5;//make mode 5 to return home after outing from this function
            lcd_sendstring("lamp off");
            _delay_ms(200);
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
  }
}

/*unsigned char key;

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

  lcd_sendstring("Starting up.");
  _delay_ms(2000);
  LCD_SendCommand(1);
  _delay_ms(100); 

  lcd_sendstring("Starting up..");
  _delay_ms(2000);
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
}*/

#endif