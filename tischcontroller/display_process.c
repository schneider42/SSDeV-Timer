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
#include "display_process.h"
#include "lcd.h"
#include "lcdhal.h"
#include "font_renderer.h"
#include "time.h"
#include "time_process.h"
#include "config.h"

#include <stdint.h>
#include <stdio.h>

void display_init(void)
{
    char buf[64];
    lcd_init();
    lcd_fill(0);
    sprintf(buf, "Tisch: %u", TABLE_NUMBER + 1); font_renders(buf, 0, 0);
    sprintf(buf, "Zeit:"); font_renders(buf, 0, 16);
    lcd_display();
}

void display_tick(void)
{
    static uint32_t s = 0;
    char buf[64];

    s++;
    if(s == 10) {
        s = 0;
        struct time *t = time_getTime();
        time_format(t, buf);
        font_renders(buf, 0, 32);
        lcd_display();
    }
}

void display_process(void)
{
}

