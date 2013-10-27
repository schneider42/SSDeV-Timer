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
#include "display_process.h"
#include "command.h"

#include <stdint.h>
#include <string.h>

#define ADDRESS_COUNT   2

static uint8_t state;
static uint8_t next_address;

void control_init(void)
{
    state = 0;
    next_address = MASTER_ADDRESS + 1;
}

void control_tick(void)
{
    static uint16_t tick = 0;
    if(tick++ == 5) {
        switch(state) {
            case 0:
                bus_send(next_address, CMD_GET_PRESS_COUNT, NULL, 0);
                next_address++;
                if(next_address == MASTER_ADDRESS + ADDRESS_COUNT) {
                    next_address = MASTER_ADDRESS + 1;
                }
                state = 0;
            break;
        }
        tick = 0;
    }
}


void control_newCommand(uint8_t address, uint8_t cmd,
                        uint8_t *data, uint8_t n)
{
    uint8_t p1;
    uint8_t table = address - MASTER_ADDRESS;
    switch(cmd) {
        case CMD_PRESS_COUNT:
            p1 = data[0];
            display_setPressCount(table, p1);
        break;
        case CMD_PRESS:
        break;
    }
}

