/*
 *  This file is part of the luftschleuse2 project.
 *
 *  See https://github.com/muccc/luftschleuse2 for more information.
 *
 *  Copyright (C) 2013 Tobias Schneider <schneider@muc.ccc.de> 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "uart.h"
#include "terminal_handler.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IF_DEBUG_RETURN     {if(debug) return;}
bool debug = false;

void terminal_handler_init(void)
{
    uart1_init(UART_BAUD_SELECT(UART_BAUDRATE, F_CPU));
}

void terminal_puts(char *s)
{
    while(*s) {
        if(*s == '\n') {
            uart1_putc('\r');
        }
        uart1_putc(*s++);
    }
}

void terminal_printf(char *fmt, ...)
{
    char buffer[128];
    va_list myargs;
    va_start(myargs, fmt);
    vsprintf(buffer, fmt, myargs);
    terminal_puts(buffer);
    va_end(myargs);
}

void terminal_reset(void)
{
    IF_DEBUG_RETURN;
	// initializes terminal to "power-on" settings
	// ESC c
	terminal_printf("\x1B\x63");
}

void terminal_clearScreen(void)
{
    IF_DEBUG_RETURN;
	// ESC [ 2 J
	terminal_printf("\x1B[2J");
}

void terminal_setAttr(uint8_t attr)
{
    IF_DEBUG_RETURN;
	// ESC [ Ps m
	terminal_printf("\x1B[%dm",attr);
}

void terminal_setCursorMode(bool visible)
{
    IF_DEBUG_RETURN;
	if(visible) {
		// ESC [ ? 25 h
		terminal_printf("\x1B[?25h");
	} else {
		// ESC [ ? 25 l
		terminal_printf("\x1B[?25l");
    }
}

void terminal_setCursorPos(uint8_t line, uint8_t col)
{
    IF_DEBUG_RETURN;
	// ESC [ Pl ; Pc H
	terminal_printf("\x1B[%d;%dH",line,col);
}

void terminal_debug(char *fmt, ...)
{
    if(!debug) {
        return;
    }
    char buffer[128];
    va_list myargs;
    va_start(myargs, fmt);
    vsprintf(buffer, fmt, myargs);
    terminal_puts(buffer);
    va_end(myargs);
}


void terminal_dumpData(uint8_t *data, uint8_t len)
{
    bool first = true;
    while(len--) {
        if(first) {
            terminal_debug("%02x", *data++);
            first = false;
        } else {
            terminal_debug(" %02x", *data++);
        }
    }
}

