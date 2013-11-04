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
#ifndef CONTROL_PROCESS_H_
#define CONTROL_PROCESS_H_

#include <stdint.h>
#include "packet.h"

void control_init(void);
void control_tick(void);
void control_process(void);
void control_newCommand(uint8_t address, uint8_t cmd,
                        uint8_t *data, uint8_t n);

const struct time * control_getTargetTime(void);

void control_getStateName(char *buf);

#endif
