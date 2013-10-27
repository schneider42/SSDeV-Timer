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

#include <stdint.h>
#include <string.h>
#include <stdio.h>

void display_init(void)
{
    lcd_init();
    lcd_fill(0);
    //int i;
    //for(i=0;i<30;i++){
    //    lcd_setPixel(i,i,true);
    //}
    //font_render('\\', 0, 0);
    //font_renders("foo bar", 20, 0);
    lcd_display();
    //while(1);
#if 0
    //static uint8_t r = 0;
    while(1){
        //if( r == 0 )
        //    r = 0xff;
        //else
        //    r = 0;
        //lcd_fill(r);
        lcd_fill(0xAA);
        lcd_display();
        //lcdhal_delayms(500);
        //lcd_startStream();

        //while(x--)
        //    lcd_stream(r,0,0);
        //lcd_stopStream();
    }
#endif
}

void display_tick(void)
{
}

void display_process(void)
{
}

void display_setPressCount(uint8_t table, uint8_t presses)
{
    char buf[64];
    sprintf(buf, "%u: %03u",  table, presses);
    uint8_t y = table == 1 ? 0 : 30;
    font_renders(buf, 0, y);
    lcd_display();
}

