/*
 * lcd.h
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

#ifndef _LCD_H_
#define _LCD_H_

#include <avr/io.h>
#include "config.h"
#include "macros.h"
#include <util/delay.h>
#include <stdint.h>


/* Variable containing the LCD display status, it should be a copy of
   the internal LCD status register. It is needed by some functions, because
   you can not read it from the LCD display. The internal LCD status is
   write-only.
   LCD_I_D_BIT  - increment/decrement cursor position when writing to LCD (1/0)
   LCD_S_BIT    - move the entire LCD screen along with cursor (1/0)
   LCD_D_BIT    - display on/off (1/0)
   LCD_C_BIT    - cursor on/off (1/0)
   LCD_B_BIT    - blink on/off (1/0)
   LCD_S_C_BIT  - move the cursor or screen (0/1)
   LCD_R_L_BIT  - shifting left or right (0/1)
   LCD_DL_BIT   - set bus width 4 bit or 8 bit (0/1)
   LCD_N_BIT    - show 2 lines or 1 line (1/0)
   LCD_F_BIT    - size of char 5x7 or 5x10 (0/1)
   default value will be 0x01C1 */

extern uint16_t       lcd_status ;

#define LCD_I_D_BIT           0
#define LCD_S_BIT             1
#define LCD_D_BIT             2
#define LCD_C_BIT             3
#define LCD_B_BIT             4
#define LCD_S_C_BIT           5
#define LCD_R_L_BIT           6
#define LCD_DL_BIT            7
#define LCD_N_BIT             8
#define LCD_F_BIT             9


/* macros contributing to readability of the source code */
#define LCD_SET_SEND_INSTRUCTION_MODE \
                          CLEARBIT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;\
                          CLEARBIT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT)
#define LCD_SET_SEND_DATA_MODE \
                          SETBIT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;\
                          CLEARBIT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT)
#define LCD_SET_GET_BUSY_FLAG_MODE \
                          CLEARBIT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;\
                          SETBIT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT)
#define LCD_SET_GET_CURRENT_POSITION_MODE LCD_SET_GET_BUSY_FLAG_MODE
#define LCD_SET_READ_DATA_MODE \
                          SETBIT (LCD_HD44780_RS_PORT, LCD_HD44780_RS_BIT) ;\
                          SETBIT (LCD_HD44780_RW_PORT, LCD_HD44780_RW_BIT)


void lcd_hd44780_strobe (void) ;
void lcd_hd44780_busy_wait_4bit (void) ;
void lcd_hd44780_busy_wait_8bit (void) ;
void lcd_hd44780_write_data_to_CG_or_DD_RAM_4bit (uint8_t data) ;
void lcd_hd44780_write_data_to_CG_or_DD_RAM_8bit (uint8_t data) ;
void lcd_hd44780_set_DD_RAM_address_4bit (char address) ;

void lcd_hd44780_clear_display_4bit (void) ;

void lcd_hd44780_return_home_4bit (void) ;

void lcd_hd44780_display_on_off_4bit (uint8_t d, uint8_t c, uint8_t b) ;

void lcd_hd44780_entry_mode_set_4bit (uint8_t inc_dec, uint8_t disp_shift) ;


#define lcd_hd44780_write_data_4bit  lcd_hd44780_write_data_to_CG_or_DD_RAM_4bit
#define lcd_hd44780_write_data_8bit  lcd_hd44780_write_data_to_CG_or_DD_RAM_8bit

#ifdef LCD_HD44780_4BIT_HARDWARE
  #define lcd_hd44780_busy_wait             lcd_hd44780_busy_wait_4bit
  #define lcd_hd44780_write_data            lcd_hd44780_write_data_4bit
  #define lcd_hd44780_set_DD_RAM_address    lcd_hd44780_set_DD_RAM_address_4bit
  #define lcd_hd44780_clear_display         lcd_hd44780_clear_display_4bit
  #define lcd_hd44780_return_home           lcd_hd44780_return_home_4bit
  #define lcd_hd44780_display_on_off        lcd_hd44780_display_on_off_4bit
  #define lcd_hd44780_entry_mode_set        lcd_hd44780_entry_mode_set_4bit
#endif

#ifdef LCD_HD44780_8BIT_HARDWARE
  #define lcd_hd44780_busy_wait             lcd_hd44780_busy_wait_8bit
  #define lcd_hd44780_write_data            lcd_hd44780_write_data_8bit
#endif


void lcd_init (void) ;
void lcd_putc (char znak) ;
void lcd_puts (char* string) ;
#define lcd_print lcd_puts
void lcd_goto_xy (uint8_t x, uint8_t y) ;
#define lcd_clear_display lcd_hd44780_busy_wait () ; lcd_hd44780_clear_display
#define lcd_return_home   lcd_hd44780_busy_wait () ; lcd_hd44780_return_home
#define lcd_display(D)    lcd_hd44780_busy_wait () ;\
                          lcd_hd44780_display_on_off (\
                                              D,\
                                              BITSET (lcd_status, LCD_C_BIT),\
                                              BITSET (lcd_status, LCD_B_BIT)) ;\
                          (D) ? SETBIT   (lcd_status, LCD_D_BIT) : \
                                CLEARBIT (lcd_status, LCD_D_BIT)
#define lcd_display_on    lcd_display (TRUE)
#define lcd_display_off   lcd_display (FALSE)
#define lcd_cursor(C)     lcd_hd44780_busy_wait () ;\
                          lcd_hd44780_display_on_off (\
                                              BITSET (lcd_status, LCD_D_BIT),\
                                              C,\
                                              BITSET (lcd_status, LCD_B_BIT)) ;\
                          (C) ? SETBIT   (lcd_status, LCD_C_BIT) : \
                                CLEARBIT (lcd_status, LCD_C_BIT)
#define lcd_cursor_on     lcd_cursor(TRUE)
#define lcd_cursor_off    lcd_cursor(FALSE)
#define lcd_blink(B)      lcd_hd44780_busy_wait () ;\
                          lcd_hd44780_display_on_off (\
                                              BITSET (lcd_status, LCD_D_BIT),\
                                              BITSET (lcd_status, LCD_C_BIT),\
                                              B) ;\
                          (B) ? SETBIT   (lcd_status, LCD_B_BIT) : \
                                CLEARBIT (lcd_status, LCD_B_BIT)
#define lcd_blink_on      lcd_blink(TRUE)
#define lcd_blink_off     lcd_blink(FALSE)

#endif /* _LCD_H_ */

