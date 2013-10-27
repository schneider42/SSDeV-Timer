#include "time.h"

#include <avr/interrupt.h>
struct time time;
struct time ticktime;
volatile struct time itime;

void time_init(void)
{
    time_clear(&time);
    time_clear(&ticktime);
    ticktime.millis = 10;
    time_set(&ticktime);
    cli();
    itime = time;
    sei();
}

void time_tick(void)
{
    time_add((struct time *)&itime, &ticktime);
}

struct time* time_getTime(void)
{
    cli();
    time = itime;
    sei();
    return &time;
}

