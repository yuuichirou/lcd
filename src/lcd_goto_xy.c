/*
 * lcd_goto_xy.c
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

void lcd_goto_xy (uint8_t x, uint8_t y)
{
  uint8_t address ;

  #if (LCD_HEIGHT == 2)
    address = x - 1 ;
    if (y == 2) address |= 0x40 ;  /* same as "if (y==2) SETBIT(address,6);" */
  #endif
  #if (LCD_HEIGHT == 4)
    address = x - 1 ;
    if (BITCLEAR (y, 0)) address |= 0x40 ;      /* checking parity (2,4,6,8) */
    if (y > 2) address += LCD_WIDTH ;
  #endif

  lcd_hd44780_busy_wait () ;
  lcd_hd44780_set_DD_RAM_address (address) ;
}
