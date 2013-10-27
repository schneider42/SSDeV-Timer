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
#include "timer1.h"

#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t timer1_timebase = 0;

ISR(TIMER1_COMPA_vect)
{
    timer1_timebase++;
}

void timer1_init(void)
{
    // 7372800 Hz / 100 Hz = 72.0 * 1024
    OCR1A = 72 - 1;
    TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);    //divide by 1024
    TIMSK1 |= 1<<OCIE1A;         //enable OCR1A interrupt
}

