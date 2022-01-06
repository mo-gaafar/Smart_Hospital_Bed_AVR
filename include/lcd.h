#ifndef _LCD_H
#define _LCD_H

// LCD modes
#define LCD_8BIT_MODE 0
#define LCD_4BIT_MODE 1
// INTERFACE
#define LCD_MODE LCD_4BIT_MODE
void LCD_Init(void);
void LCD_SendCommand(unsigned char command);
void LCD_SendData(unsigned char DATA);
void lcd_setcursor(unsigned char x, unsigned char y);
void lcd_sendstring(const char *str);
void lcd_sendSpecialCharachter(unsigned char *arr, unsigned char patternno, unsigned char x, unsigned char y);

#endif