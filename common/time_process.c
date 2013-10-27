#include "time.h"

struct time time;
struct time ticktime;

void time_init(void)
{
    time_clear(&time);
    time_clear(&ticktime);
    ticktime.millis = 10;
    time_set(&ticktime);
}

void time_tick(void)
{
    time_add(&time, &ticktime);
}

struct time* time_getTime(void)
{
    return &time;
}

