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
#include "press_handler.h"

#include <string.h>

void terminal_init(void)
{
    terminal_handler_init();
    terminal_reset();
    terminal_setCursorMode(false);
}

void terminal_showTime(const struct button_press *press)
{
    char buf[64];
    struct time press_time = {.timestamp = press->timestamp};
    time_setFromTimestamp(&press_time);
    time_format(&press_time, buf);
    terminal_printf("%2u\t%2u\t%s\n", press->table + 1, press->button + 1, buf);
}

void terminal_tick(void)
{
    static uint32_t s = 0;
    //static uint32_t t = 0;
    char buf[64];
    
    s++;
    if(s == 50) {
        s = 0;
        terminal_setCursorPos(0, 5);
        terminal_printf("Master Controller");
        terminal_setCursorPos(3, 0);
        terminal_printf("Nummer\tTisch\tPlatz\tZeit\t");       

        terminal_setCursorPos(0, 25);
        const struct time *t = time_getTime();
        time_format(t, buf);
        terminal_printf(buf);
        
        terminal_setCursorPos(0, 35);
        time_format(control_getTargetTime(), buf);
        terminal_printf(buf);

        terminal_setCursorPos(0, 45);
        control_getStateName(buf);
        terminal_printf("%s", buf);

        terminal_setCursorPos(4, 0);
        uint8_t press_number;
        
        uint8_t total_presses_count = press_getTotalPressesCount();
        uint8_t i = 0;
        uint8_t j = 0;
        for(press_number = 0; press_number < total_presses_count; press_number++) {
            terminal_setCursorPos(4 + i, j * 40);
            const struct button_press *press = press_getSortedPress(press_number);
            terminal_printf("%2u\t", press_number + 1);
            terminal_showTime(press);
            i++;
            if(i > 29) {
                i = 0;
                j++;
            }
        }
    }
}

void terminal_process(void)
{
}

