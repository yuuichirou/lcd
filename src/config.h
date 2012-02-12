/*
 * config.h
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

#define LCD_HD44780_DATA_PORT PORTC
#define LCD_HD44780_DATA_PIN  PINC

#define LCD_HD44780_RW_PORT   PORTD
#define LCD_HD44780_RW_BIT    PD6
#define LCD_HD44780_RS_PORT   PORTD
#define LCD_HD44780_RS_BIT    PD7
#define LCD_HD44780_E_PORT    PORTD
#define LCD_HD44780_E_BIT     PD2

#define LCD_HD44780_4BIT_HARDWARE
/* #define LCD_HD44780_8BIT_HARDWARE */

#define LCD_HD44780_D0        PC0
#define LCD_HD44780_D1        PC1
#define LCD_HD44780_D2        PC2
#define LCD_HD44780_D3        PC3
#define LCD_HD44780_D4        PC0
#define LCD_HD44780_D5        PC1
#define LCD_HD44780_D6        PC2
#define LCD_HD44780_D7        PC3

#define LCD_HD44780_DATA_PORT_ON_LO_NIBBLE_PINS
/* #define LCD_HD44780_DATA_PORT_ON_HI_NIBBLE_PINS */
/* #define LCD_HD44780_DATA_PORT_ON_DIFFERENT_PINS */

#define LCD_WIDTH             16
#define LCD_HEIGHT            2

