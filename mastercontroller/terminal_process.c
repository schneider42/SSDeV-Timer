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
#include "terminal_process.h"
#include "terminal_handler.h"
#include "buttons.h"
#include "time_process.h"
#include "time.h"
#include "font_renderer.h"
#include "lcd.h"

#include <string.h>

void terminal_init(void)
{
    terminal_handler_init();
    terminal_setCursorPos(0, 5);
    terminal_puts("Master Controller");
}

void terminal_tick(void)
{
    static uint32_t s = 0;
    //static uint32_t t = 0;
    char buf[64];

    s++;
    if(s == 10) {
        terminal_setCursorPos(3, 5);
        s = 0;
        struct time *t = time_getTime();
        time_format(t, buf);
        terminal_puts(buf);
        font_renders(buf, 0, 50);
        lcd_display();


        uint32_t buttons = buttons_getPressed();
        uint8_t i;

        for(i = 0; i < 32; i++) {
            terminal_setCursorPos(i + 4, 0);
            if(buttons & (1 << i)) {
                terminal_printf("pressed");
            } else {
                terminal_printf("       ");
            }
        }
    }
}

void terminal_process(void)
{
}

