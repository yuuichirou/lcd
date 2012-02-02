#include "lcd.h"

void lcd_hd44780_busy_wait_8bit (void)
{
  uint8_t temp ;
  LCD_SET_GET_BUSY_FLAG_MODE ;
  PIN_INPUT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
  CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ; 
  do
  {
    lcd_hd44780_strobe () ;
    temp = BITSET (LCD_HD44780_DATA_PIN, LCD_HD44780_D7) ;
    if (temp) _delay_us(1) ;
  } while (temp) ;
  PIN_OUTPUT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
}

void lcd_hd44780_busy_wait_4bit (void)
{
  uint8_t temp ;
  LCD_SET_GET_BUSY_FLAG_MODE ;
  PIN_INPUT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
  CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
  do
  {
    lcd_hd44780_strobe () ;
    temp = BITSET (LCD_HD44780_DATA_PIN, LCD_HD44780_D7) ;
    lcd_hd44780_strobe () ;
    if (temp) _delay_us(1) ;
  } while (temp) ;
  PIN_OUTPUT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
}

