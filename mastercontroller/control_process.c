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
#include "press_handler.h"
#include "config.h"
#include "terminal_process.h"

#include <stdint.h>
#include <string.h>

struct button_press button_presses[TABLE_COUNT][BUTTONS_COUNT * PRESSES_COUNT];
uint8_t presses_count[TABLE_COUNT];

static enum {
    STOP,
    SET_TIME,
    RUN,
    HOLD
} state;

const char * states[] = { "STOP    ",
                        "SET_TIME",
                        "RUN     ",
                        "HOLD    "};

static uint8_t next_address;
static struct time target_time;
static struct time step_time;

void control_getStateName(char *buf)
{
    strcpy(buf, states[state]);
}

void control_init(void)
{
    press_init();

    state = 0;
    next_address = MASTER_ADDRESS + 1;
    target_time.timestamp = 1000 * 60UL * 5;
    time_setFromTimestamp(&target_time);

    step_time.timestamp = 1000 * 60UL;
    time_setFromTimestamp(&step_time);
}

void rotate_address(void)
{
    next_address++;
    if(next_address == MASTER_ADDRESS + TABLE_COUNT + 1) {
        next_address = MASTER_ADDRESS + 1;
    }
}

void control_tick(void)
{
    static uint16_t tick = 0;
    struct time temp_time;

    if(tick++ == 5) {
        uint32_t buttons = buttons_getPressed();
        switch(state) {
            case STOP:
                if(buttons & BUTTON_1) {
                    state = SET_TIME;
                }else if(buttons & BUTTON_2) {
                    time_start();
                    press_init();
                    terminal_init();
                    state = RUN;
                }else{
                    temp_time.timestamp = 0;
                    time_setFromTimestamp(&temp_time);
                    time_stop();
                    time_setTime(&temp_time);
                    bus_send(BROADCAST_ADDRESS, CMD_SET_TIME, (uint8_t*) time_getTime(), sizeof(struct time));
                    bus_send(BROADCAST_ADDRESS, CMD_RESET_PRESSES, NULL, 0); 
                    state = STOP;
                }
            break;
            case SET_TIME:
                if(buttons & BUTTON_1) {
                    state = STOP;
                }else if(buttons & BUTTON_2) {
                    time_add(&target_time, &step_time);
                    state = SET_TIME;
                }else if(buttons & BUTTON_3) {
                    time_subtract(&target_time, &step_time);
                    state = SET_TIME;
                }
            break;
            case RUN:
                if(buttons & BUTTON_1) {
                    state = STOP;
                }else if(buttons & BUTTON_3) {
                    state = HOLD;
                }else{
                    bus_send(BROADCAST_ADDRESS, CMD_SET_TIME, (uint8_t*) time_getTime(), sizeof(struct time));
                    bus_send(next_address, CMD_GET_PRESS_COUNT, NULL, 0);
                    rotate_address();
                    if(time_getTime()->timestamp >= target_time.timestamp) {
                        state = HOLD;
                    }else{
                        state = RUN;
                    }
                }
            break;
            case HOLD:
                if(buttons & BUTTON_1) {
                    state = STOP;
                }else if(buttons & BUTTON_3) {
                    time_start();
                    state = RUN;
                }else{
                    time_stop();
                    bus_send(BROADCAST_ADDRESS, CMD_SET_TIME, (uint8_t*) time_getTime(), sizeof(struct time));
                    state = HOLD;
                }
            break;
        }
        tick = 0;
    }
}

static void cmd_press_count(uint8_t address, uint8_t table,
                            uint8_t *data, uint8_t n)
{
    uint8_t press_count = data[0];
    uint8_t known_press_count = press_getPressesCount(table);

    display_setPressCount(table, press_count);
    if(press_count > known_press_count) {
        bus_send(address, CMD_GET_PRESS, &known_press_count, 1);
    }
}

static void cmd_press(uint8_t address, uint8_t table,
                        uint8_t *data, uint8_t n)
{
    struct button_press p; 
    uint8_t press_number = data[0];

    // I don't want to deal with aliasing...
    memcpy(&p, data + 1, sizeof(p)); 
    press_addPress(table, press_number, &p);
}

void control_newCommand(uint8_t address, uint8_t cmd,
                        uint8_t *data, uint8_t n)
{
    uint8_t table = address - MASTER_ADDRESS - 1;

    switch(cmd) {
        case CMD_PRESS_COUNT:
            cmd_press_count(address, table, data, n);
        break;
        case CMD_PRESS:
            cmd_press(address, table, data, n);
        break;
    }
}

const struct time * control_getTargetTime(void)
{
    return &target_time;
}
