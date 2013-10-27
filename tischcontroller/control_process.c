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
#include "control_process.h"
#include "buttons.h"
#include "packet.h"
#include "time_process.h"
#include "bus_process.h"
#include "command.h"

#include <stdint.h>
#include <string.h>
#define BUTTONS_COUNT   12
#define PRESSES_COUNT   5

struct button_press {
    uint32_t timestamp;
    uint8_t button;
};

struct button_press button_presses[BUTTONS_COUNT * PRESSES_COUNT];
uint8_t presses;

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

static void reset_presses(void)
{
    uint8_t i;
    for(i = 0; i < ELEMENTS(button_presses); i++) {
        button_presses[i].timestamp = 0;
        button_presses[i].button = 0;
    }
    presses = 0;
}

void control_init(void)
{
    reset_presses();
}

void control_tick(void)
{
}

static void control_buttonPressed(uint8_t button)
{
    struct time *t = time_getTime();
    uint8_t i;
    for(i = 0; i < ELEMENTS(button_presses); i++) {
        if(button_presses[i].button == button) {
            if(t->timestamp - button_presses[i].timestamp < 1000) {
                return;
            }
        }
    }

    if(presses < ELEMENTS(button_presses)) {
        button_presses[presses].timestamp = t->timestamp;
        button_presses[presses].button = button;
        presses++;
    }
}

void control_process(void)
{
    uint32_t buttons = buttons_getPressed();
    uint8_t i;
    for(i = 0; i < 12; i++) {
        if(buttons & 0x01) {
            control_buttonPressed(i);
        }
        buttons >>= 1;
    }
}

void control_newCommand(uint8_t cmd, uint8_t *data, uint8_t n)
{
    uint8_t p1;
    switch(cmd) {
        case CMD_GET_PRESS_COUNT:
            bus_reply(CMD_PRESS_COUNT, (uint8_t *)&presses, 1);
        break;
        case CMD_GET_PRESS:
            p1 = data[0];
            if(p1 < presses) {
                bus_reply(CMD_PRESS,
                    (uint8_t *)&button_presses[p1],
                    sizeof(button_presses[p1]));
            }
        break;
        case CMD_RESET_PRESSES:
            reset_presses();
        break;
        case CMD_SET_TIME:
        break;
    }
}

#if 0
static void control_sendState(void)
{
   packet_t p;
   serial_sendPacket(&p);
}
#endif
