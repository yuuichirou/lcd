/*
 * lcd_init.c
 * This file is part of the set of functions to handle alphanumeric displays.
 *
 * Copyright (C) 2012 Krzysztof Kozik
 *
 * This set is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
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


void lcd_init (void)
{
  PIN_OUTPUT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT) ;
  PIN_OUTPUT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;
  PIN_OUTPUT (LCD_HD44780_E_PORT,  LCD_HD44780_E_BIT) ;

  PINS_OUTPUT (LCD_HD44780_DATA_PORT, BIT(LCD_HD44780_D0) |
                                      BIT(LCD_HD44780_D1) |
                                      BIT(LCD_HD44780_D2) |
                                      BIT(LCD_HD44780_D3) |
                                      BIT(LCD_HD44780_D4) |
                                      BIT(LCD_HD44780_D5) |
                                      BIT(LCD_HD44780_D6) |
                                      BIT(LCD_HD44780_D7)) ;

  CLEARBIT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;
  CLEARBIT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT) ;
  CLEARBIT (LCD_HD44780_E_PORT,  LCD_HD44780_E_BIT) ;

  CLEARBITS (LCD_HD44780_DATA_PORT, BIT(LCD_HD44780_D0) |
                                    BIT(LCD_HD44780_D1) |
                                    BIT(LCD_HD44780_D2) |
                                    BIT(LCD_HD44780_D3) |
                                    BIT(LCD_HD44780_D4) |
                                    BIT(LCD_HD44780_D5) |
                                    BIT(LCD_HD44780_D6) |
                                    BIT(LCD_HD44780_D7)) ;

  lcd_status = 0x1C1 ;
  _delay_ms (15) ;

  /* LCD HD44780 driver software initialization starts here*/

  /* sets bus width to 8 bit DATA PORT = 0011 00 xx */
  LCD_SET_SEND_INSTRUCTION_MODE ;
  SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D4) ;
  SETBIT (LCD_HD44780_DATA_PORT, LCD_HD44780_D5) ;

  lcd_hd44780_strobe () ;
  _delay_ms (5) ;
  lcd_hd44780_strobe () ;
  _delay_us (100) ;
  lcd_hd44780_strobe () ;

  /* LCD HD44780 driver software initialization ends here*/
}

