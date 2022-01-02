#ifndef lcd
#define lcd

//lcd modes
#define LCD_8bit_MODE 0
#define LCD_4bit_MODE 1
//INTERFACE
#define lcd_MODE LCD_4bit_MODE
void LCD_INIT(void);
void LCD_SendCommand(u8 command);
void LCD_SendData(u8 DATA);
void lcd_setcursor(u8 x,u8 y);
void lcd_sendstring(const u8 * str);
void lcd_sendSpecialCharachter(u8 *arr,u8 patternno,u8 x,u8 y);


#endif