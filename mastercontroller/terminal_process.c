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
//#include "font_renderer.h"
//#include "lcd.h"
#include "buttons.h"
#include "control_process.h"

#include <string.h>

void terminal_init(void)
{
    terminal_handler_init();
    terminal_setCursorPos(0, 5);
    terminal_puts("Master Controller");
    terminal_setCursorPos(3, 0);
    terminal_printf("Tisch\tPlatz\tZeit\t");
}

void terminal_showTime(uint8_t table, struct button_press *press)
{
    char buf[64];
    struct time press_time;
    time_setFromTimestamp(&press_time, press->timestamp);
    time_format(&press_time, buf);
    terminal_printf("%u\t%u\t%s\n", table + 1, press->button + 1, buf);
}

void terminal_tick(void)
{
    static uint32_t s = 0;
    //static uint32_t t = 0;
    char buf[64];
    
    s++;
    if(s == 50) {
        terminal_setCursorPos(0, 25);
        s = 0;
        struct time *t = time_getTime();
        time_format(t, buf);
        terminal_puts(buf);
        terminal_setCursorPos(4, 0);

        uint8_t table, press_number;
        
        for(table = 0; table < TABLE_COUNT; table++) {
            uint8_t presses_count = control_getPressesCount(table);
            for(press_number = 0; press_number < presses_count; press_number++) {
                struct button_press press = control_getPress(table, press_number);
                terminal_showTime(table, &press);
            }
        }
    }
}

void terminal_process(void)
{
}

