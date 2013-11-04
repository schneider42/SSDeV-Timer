#include "time.h"

#include <avr/interrupt.h>
#include <stdbool.h>

struct time time;
struct time ticktime;
volatile struct time itime;
static volatile bool running;

void time_init(void)
{
    time_clear(&time);
    time_clear(&ticktime);
    ticktime.millis = 10;
    time_set(&ticktime);
    running = true;
    cli();
    itime = time;
    sei();
}

void time_tick(void)
{
    if(running) {
        time_add((struct time *)&itime, &ticktime);
    }
}

struct time * time_getTime(void)
{
    cli();
    time = itime;
    sei();
    return &time;
}

void time_setTime(const struct time *t)
{
    cli();
    itime = *t;
    sei();
}

void time_stop(void)
{
    running = false;
}

void time_start(void)
{
    running = true;
}
