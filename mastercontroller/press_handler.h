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
#ifndef PRESS_HANDLER_H_
#define PRESS_HANDLER_H_
#include "buttons.h"
#include "config.h"

#include <stdint.h>
#include <string.h>

void press_init(void);
uint8_t press_getPressesCount(uint8_t table);
uint8_t press_getTotalPressesCount(void);
const struct button_press *press_getSortedPress(uint8_t press_number);
void press_addPress(uint8_t table, uint8_t press_number, const struct button_press *press);

#endif
