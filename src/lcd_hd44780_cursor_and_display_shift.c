/*
 * lcd_hd44780_cursor_and_display_shift.c
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
#include <avr/io.h>

void lcd_hd44780_cursor_and_display_shift_4bit (uint8_t s_c, uint8_t r_l)
{
  LCD_SET_SEND_INSTRUCTION_MODE ;
  CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D5) |
                                    BIT (LCD_HD44780_D6) |
                                    BIT (LCD_HD44780_D7)) ;
  SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) ;
  lcd_hd44780_strobe () ;
  s_c ? SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) :
        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) ;
  r_l ? SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) :
        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) ;
  CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                    BIT (LCD_HD44780_D1)) ;
  lcd_hd44780_strobe () ;
}

