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
#include "packet.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <util/crc16.h>

static uint16_t calculate_crc(packet_t *p)
{
    uint8_t i;
    uint16_t crc = 0xffff;
    uint8_t *d = (uint8_t *)p;

    for(i = 0; i < sizeof(packet_t) - 2; i++) {
        crc = _crc16_update(crc, *d++);
    }

    return crc;
}

bool packet_checkCRC(packet_t *p)
{
    return calculate_crc(p) == p->crc;
}

void packet_setCRC(packet_t *p)
{
    p->crc = calculate_crc(p);
}
