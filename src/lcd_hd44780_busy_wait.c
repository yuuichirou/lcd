/*
 * lcd_hd44780_busy_wait.c
 * This file is part of the set of functions to handle alphanumeric displays.
 *
 * Copyright (C) 2012 Krzysztof Kozik
 *
 * This set is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "lcd.h"
#include "macros.h"

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
    if (temp) _delay_us (1) ;
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
    if (temp) _delay_us (1) ;
  } while (temp) ;
  PIN_OUTPUT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
}

