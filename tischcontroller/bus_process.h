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
#ifndef BUS_PROCESS_H_
#define BUS_PROCESS_H_
#include "packet.h"

#define MASTER_ADDRESS      1
#define NODE_ADDRESS     (MASTER_ADDRESS + TABLE_NUMBER + 1)
#define BROADCAST_ADDRESS   0xFF

void bus_init(void);
void bus_tick(void);
void bus_process(void);
void bus_reply(uint8_t cmd, uint8_t *data, uint8_t len);

#endif
