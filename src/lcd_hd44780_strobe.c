#include "lcd.h"

void lcd_hd44780_strobe (void)
{
	SETBIT (LCD_HD44780_E_PORT, LCD_HD44780_E_BIT) ;
	_delay_us (1) ;
	CLEARBIT (LCD_HD44780_E_PORT, LCD_HD44780_E_BIT) ;
}
