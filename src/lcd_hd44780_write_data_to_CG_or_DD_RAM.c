/*
 * lcd_hd44780_write_data_to_CG_or_DD_RAM.c
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

void lcd_hd44780_write_data_to_CG_or_DD_RAM_4bit (uint8_t data)
{
  LCD_SET_SEND_DATA_MODE ;
  #ifdef LCD_HD44780_DATA_PORT_ON_DIFFERENT_PINS
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D4) |
                                      BIT (LCD_HD44780_D5) |
                                      BIT (LCD_HD44780_D6) |
                                      BIT (LCD_HD44780_D7)) ;
    BITVAL (data, 7) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
    BITVAL (data, 6) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D6) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D6) ;
    BITVAL (data, 5) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D5) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D5) ;
    BITVAL (data, 4) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) ;
    lcd_hd44780_strobe () ;

    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                      BIT (LCD_HD44780_D1) |
                                      BIT (LCD_HD44780_D2) |
                                      BIT (LCD_HD44780_D3)) ;
    BITVAL (data, 3) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) ;
    BITVAL (data, 2) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) ;
    BITVAL (data, 1) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D1) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D1) ;
    BITVAL (data, 0) ?
                     SETBIT   (LCD_HD44780_DATA_PORT, LCD_HD44780_D0) :
                     CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D0) ;
    lcd_hd44780_strobe () ;
  #endif
  #ifdef LCD_HD44780_DATA_PORT_ON_LO_NIBBLE_PINS
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D4) |
                                      BIT (LCD_HD44780_D5) |
                                      BIT (LCD_HD44780_D6) |
                                      BIT (LCD_HD44780_D7)) ;
    LCD_HD44780_DATA_PORT |= (data >> 4) ;
    lcd_hd44780_strobe () ;
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                      BIT (LCD_HD44780_D1) |
                                      BIT (LCD_HD44780_D2) |
                                      BIT (LCD_HD44780_D3)) ;
    LCD_HD44780_DATA_PORT |= (data & 0x0F) ;
    lcd_hd44780_strobe () ;
  #endif
  #ifdef LCD_HD44780_DATA_PORT_ON_HI_NIBBLE_PINS
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D4) |
                                      BIT (LCD_HD44780_D5) |
                                      BIT (LCD_HD44780_D6) |
                                      BIT (LCD_HD44780_D7)) ;
    LCD_HD44780_DATA_PORT |= (data & 0xF0) ;
    lcd_hd44780_strobe () ;
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                      BIT (LCD_HD44780_D1) |
                                      BIT (LCD_HD44780_D2) |
                                      BIT (LCD_HD44780_D3)) ;
    LCD_HD44780_DATA_PORT |= (data << 4) ;
    lcd_hd44780_strobe () ;
  #endif
}

void lcd_hd44780_write_data_to_CG_or_DD_RAM_8bit (uint8_t data)
{
  LCD_SET_SEND_DATA_MODE ;
  LCD_HD44780_DATA_PORT = data ;
  lcd_hd44780_strobe () ;
}

