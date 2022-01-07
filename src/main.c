#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ADC.h"
#include "pushbuttons.h"
#include "lcd.h"
#include "servo.h"
#include "timer.h"
#include "loadcell.h"

// GLOBAL VARIABLE DEFINITIONS

// MENU VARS
unsigned char key, c, tt;

// WEIGHT
unsigned short CURRENT_Weight; // Current measured weight
unsigned char ALARM_Weight;    // This is set if weight exceeds threshold
unsigned short OCCUPANCY_Time; // Time current weight is above zero
#define MAX_Weight 50

// TEMPERATURE
unsigned short BODY_Temp;             // Body Temperature (sensor1 at ADC A2)
unsigned char ALARM_Fever;            // This is set if body temp is above 37
unsigned short ROOM_Temp;             // Room Temperature (sensor 2 at ADC A3)
unsigned short HEATER_Threshold = 10; // Temperature to be compared with ROOM_Temp for heater relay control, is set by LCD menu
unsigned char HEATER_Enable = 0;      // Is heater enabled? (done from lcd menu)
unsigned char HEATER_State = 0;       // If set, heater relay is turned on

// LIGHT
unsigned char LIGHT_Enable = 0; // Is light enabled (done from lcd menu)
unsigned char LIGHT_State = 0;  // If set, light relay is turned on

// TODO: Decide on mode change logic

// TIMER VARS
unsigned char TIMER0_Counter = 0; // counter to help increase the timer interrupt to 100ms
#define TIMER0_Counter_Max 6      // 16ms * 6 = 96ms

// INTERRUPT FUNCTION EACH 100ms
ISR(TIMER0_OVF_vect)
{
  TIMER0_Counter++;
  if (TIMER0_Counter == TIMER0_Counter_Max)
  {
    // START

    // ------------WEIGHT------------------//
    // Refresh current weight from adc
    CURRENT_Weight = LOADCELL_ReadWeight();
    // Check if max rated weight exceeded
    if (CURRENT_Weight > MAX_Weight)
    {
      // TODO:PRINT ALARM ???
      ALARM_Weight = 1;
    }
    else if (CURRENT_Weight > 0) // if weight within operating range
    {
      OCCUPANCY_Time++; // each 100ms
    }
    else
    {
      OCCUPANCY_Time = 0; // if not used
    }

    //-------------TEMPERATURE-----------//
    BODY_Temp = ADC_Read(2); // TODO: review adc read arguments
    ROOM_Temp = ADC_Read(3); // TODO: missing in hardware

    // END of scope
    TIMER0_Counter = 0;
  }
}

// SLEEP_Activate(){

// }

#define DEBUGMODE 1
#if DEBUGMODE

int main(void)
{
  unsigned char buttonpressed;

  ADC_Init();
  TIMER0_Init();
  LOADCELL_Init();
  PUSHBUTTONS_Init();
  LCD_Init();

  while (1)
  {

    LCD_SendCommand(1);
    lcd_setcursor(10, 0);
    lcd_sendstring("      heating");
    lcd_setcursor(1, 0);
    lcd_sendstring("1:on");
    lcd_sendstring("  2:off ");

    _delay_ms(500);
  }

  return 0;
}

#else

void sleep1(void)
{
  lcd_sendstring("sleeping");
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
void sit1(void)
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
void sit2(void)
{
  LCD_SendCommand(1);
  lcd_sendstring("heating");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:on");
  lcd_sendstring("  2:off ");
}
void sit3(void)
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
void sit4()
{
  LCD_SendCommand(1);
  lcd_sendstring("lamp enable");
  lcd_setcursor(1, 0);
  lcd_sendstring("1:on");
  lcd_sendstring("  2:off ");
}

unsigned char choose(void)
{
  do
  {

    key = PUSHBUTTONS_Read();

  } while (key == 0xff);
  return key;
}
int main(void)
{
  ADC_Init();
  TIMER0_Init();
  LOADCELL_Init();
  PUSHBUTTONS_Init();
  LCD_Init();

  unsigned char mode = 5, Pass = 0, ff = 0;
  lcd_setcursor(0, 4);
  lcd_sendstring("WELCOME!");
  _delay_ms(300);
  LCD_SendCommand(1);
  lcd_setcursor(0, 10);
  lcd_sendstring("For Login");
  lcd_setcursor(1, 3);
  lcd_sendstring("Press :  1");
  key = choose();
  if (key == 1)
  {
    LCD_SendCommand(1);
    while (Pass != 4)
    {
      ff = 0;
      LCD_SendCommand(1);
      lcd_sendstring("USER : Hassan");
      lcd_setcursor(1, 0);
      lcd_sendstring("PASS : ");
      while (ff != 4)
      {
        key = choose();
        LCD_SendData(key + '0');
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

  else
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
      sit1();
      mode = choose();
      if (mode == 1)
      {

        sit2();
        mode = choose();
        if (mode == 1)
        {
          LCD_SendCommand(1);
          lcd_sendstring("heater on");
          _delay_ms(200);
          LCD_SendCommand(1);
          sit3();
          while (c != 2)
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
          sit4();
          mode = choose();
          if (mode == 1)
          {
            LCD_SendCommand(1);
            mode = 5;
            lcd_sendstring("lamp on");
            _delay_ms(200);
          }
          else if (mode == 2)
          {
            LCD_SendCommand(1);
            mode = 5;
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
    key = PUSHBUTTONS_Read();

  } while (key == 0xff);
  return key;
}

int main(void)
{
  //_delay_ms(200);
  unsigned char mode = 5;
  LCD_Init();
  PUSHBUTTONS_Init();

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