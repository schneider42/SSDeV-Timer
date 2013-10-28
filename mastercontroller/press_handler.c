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
#include "buttons.h"
#include "config.h"
#include "sort.h"

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

struct button_press button_presses[TABLE_COUNT * BUTTONS_COUNT * PRESSES_COUNT];
const struct button_press * button_presses_sorted[ELEMENTS(button_presses)];

uint8_t presses_count[TABLE_COUNT];
uint8_t total_presses;


void press_init(void)
{
    uint8_t i;
    for(i = 0; i < ELEMENTS(presses_count); i++) {
        presses_count[i] = 0;
    }
    total_presses = 0;
}

bool press_gt(const struct button_press *p1, const struct button_press *p2)
{
    if(p1->timestamp < p2->timestamp) {
        return false;
    }

    if(p1->timestamp == p2->timestamp) {
        if(p1->button < p2->button) {
            return false;
        }
        if(p1->button == p2->button) {
            if(p1->table <= p2->table) {
                return false; 
            }
        }
    }
    return true;
}

static void presses_sort(void)
{
    uint8_t i;
    for(i = 0; i < total_presses; i++) {
        button_presses_sorted[i] = &button_presses[i];
    }
    sort((void **)button_presses_sorted, (bool (*)(void *, void *))press_gt, total_presses);
}

uint8_t press_getPressesCount(uint8_t table)
{
    return presses_count[table];
}

uint8_t press_getTotalPressesCount(void)
{
    return total_presses;
}

const struct button_press *press_getSortedPress(uint8_t press_number)
{
    return button_presses_sorted[press_number];
}

void press_addPress(uint8_t table, uint8_t press_number, const struct button_press *press)
{
    if( presses_count[table] == press_number) {
        button_presses[total_presses] = *press;
        total_presses++;
        presses_count[table]++;
        presses_sort();
    }
}

