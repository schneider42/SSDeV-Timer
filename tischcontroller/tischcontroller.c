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
#include "config.h"
#include "control_process.h"
#include "bus_handler.h"
#include "bus_process.h"
#include "display_process.h"
#include "buttons.h"
#include "time_process.h"

void tischcontroller_init(void)
{
    time_init();
    buttons_init();
    display_init();
    bus_handler_init();
    bus_init();
    control_init();
}

void tischcontroller_tick(void)
{
    buttons_tick();
    bus_tick();
    control_tick();
    display_tick();
}

void tischcontroller_process(void)
{
    bus_process();
    control_tick();
    display_process();
}

