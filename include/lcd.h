
#ifndef LCD_H
#define LCD_H

/* LCD Modes */
#define LCD_8BIT_MODE 0
#define LCD_4BIT_MODE 1

/* User Input */
#define LCD_MODE LCD_4BIT_MODE

void LCD_Init(void);

void LCD_SendCommand(unsigned char Command);

void LCD_SendData(unsigned char Data);

void lcd_setcursor(unsigned char x, unsigned char y);
// void Seperate_Result (float u32Result,unsigned char * u8array_Result);
void lcd_send_number(unsigned char numb);

void lcd_sendstring(const char *Str);
void send_specialcharachter(unsigned char *arr, char patternno, char x, char y);

#endif /* LCD_H */
