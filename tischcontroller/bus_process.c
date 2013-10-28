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
#include "bus_process.h"
#include "bus_handler.h"
#include "config.h"
#include "packet.h"
#include "control_process.h"

#include <stdint.h>
#include <string.h>

void bus_init(void)
{
    bus_handler_init();
}

void bus_tick(void)
{
}

void bus_process(void)
{
    uint8_t channel = bus_readFrame();
    uint8_t len = bus_getMessageLen();
    if( len && channel ){
        if(channel == NODE_ADDRESS) {
            packet_t *p = (packet_t *)bus_getMessage();
            if(packet_checkCRC(p)) {
                control_newCommand(p->cmd,
                    p->data, sizeof(p->data));
            }
        }
    }
}

void bus_reply(uint8_t cmd, uint8_t *data, uint8_t len)
{
    packet_t p;
    p.cmd = cmd;
    memcpy(p.data, data, len);
    packet_setCRC(&p);
    bus_sendFrame(NODE_ADDRESS, (uint8_t *)&p, sizeof(p));
}








