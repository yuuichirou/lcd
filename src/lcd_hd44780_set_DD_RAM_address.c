/*
 * lcd_hd44780_set_DD_RAM_address.c
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

void lcd_hd44780_set_DD_RAM_address_4bit (char address)
{
  LCD_SET_SEND_INSTRUCTION_MODE ;
  SETBIT (address, 7) ;
  #ifdef LCD_HD44780_DATA_PORT_ON_DIFFERENT_PINS
    /* BITVAL (address, 7) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ; */
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D7) ;
    BITVAL (address, 6) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D6) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D6) ;
    BITVAL (address, 5) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D5) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D5) ;
    BITVAL (address, 4) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) ;
    lcd_hd44780_strobe () ;

    BITVAL (address, 3) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D3) ;
    BITVAL (address, 2) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D2) ;
    BITVAL (address, 1) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D1) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D1) ;
    BITVAL (address, 0) ?
                        SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D0) :
                        CLEARBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D0) ;
    lcd_hd44780_strobe () ;
  #endif
  #ifdef LCD_HD44780_DATA_PORT_ON_LO_NIBBLE_PINS
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D4) |
                                      BIT (LCD_HD44780_D5) |
                                      BIT (LCD_HD44780_D6) |
                                      BIT (LCD_HD44780_D7)) ;
    LCD_HD44780_DATA_PORT = LCD_HD44780_DATA_PORT | (address >> 4) ;
    lcd_hd44780_strobe () ;
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                      BIT (LCD_HD44780_D1) |
                                      BIT (LCD_HD44780_D2) |
                                      BIT (LCD_HD44780_D3)) ;
    LCD_HD44780_DATA_PORT = LCD_HD44780_DATA_PORT | (address & 0x0F) ;
    lcd_hd44780_strobe () ;
  #endif
  #ifdef LCD_HD44780_DATA_PORT_ON_HI_NIBBLE_PINS
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D4) |
                                      BIT (LCD_HD44780_D5) |
                                      BIT (LCD_HD44780_D6) |
                                      BIT (LCD_HD44780_D7)) ;
    LCD_HD44780_DATA_PORT |= (address & 0xF0) ;
    lcd_hd44780_strobe () ;
    CLEARBITS (LCD_HD44780_DATA_PORT, BIT (LCD_HD44780_D0) |
                                      BIT (LCD_HD44780_D1) |
                                      BIT (LCD_HD44780_D2) |
                                      BIT (LCD_HD44780_D3)) ;
    LCD_HD44780_DATA_PORT |= (address << 4) ;
    lcd_hd44780_strobe () ;
  #endif
}

void lcd_hd44780_set_DD_RAM_address_8bit (char address)
{
        /* TO DO */
}

