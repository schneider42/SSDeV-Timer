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
#ifndef TERMINAL_HANDLER
#define TERMINAL_HANDLER

#include "config.h"
#include "uart.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#define VT100_ATTR_OFF		0
#define VT100_BOLD			1
#define VT100_USCORE		4
#define VT100_BLINK			5
#define VT100_REVERSE		7
#define VT100_BOLD_OFF		21
#define VT100_USCORE_OFF	24
#define VT100_BLINK_OFF		25
#define VT100_REVERSE_OFF	27

extern void terminal_handler_init(void);
extern void terminal_puts(char *s);
void terminal_printf(char *fmt, ...);
void terminal_reset(void);
void terminal_clearScreen(void);
void terminal_setAttr(uint8_t attr);
void terminal_setCursorMode(bool visible);
void terminal_setCursorPos(uint8_t line, uint8_t col);

#endif
