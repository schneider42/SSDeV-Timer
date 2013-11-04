#include "time.h"
#include <stdint.h>
#include <stdio.h>

void time_clear(struct time *t)
{
    t->timestamp = 0;
    t->millis = 0;
    t->seconds = 0;
    t->minutes = 0;
    t->hours = 0;
}

void time_add(struct time *t1, const struct time *t2)
{
    t1->timestamp += t2->timestamp;

    t1->millis += t2->millis;
    while(t1->millis > 999) {
        t1->millis -= 1000;
        t1->seconds++;
    }

    t1->seconds += t2->seconds;
    while(t1->seconds > 59) {
        t1->seconds -= 60;
        t1->minutes++;
    }

    t1->minutes += t2->minutes;
    while(t1->minutes > 59) {
        t1->minutes -= 60;
        t1->hours++;
    }

    t1->hours += t2->hours;
}

void time_subtract(struct time *t1, const struct time *t2)
{
    if(t1->timestamp <= t2->timestamp){
        t1->timestamp = 0;
        t1->millis = 0;
        t1->seconds = 0;
        t1->minutes = 0;
        t1->hours = 0;
        return;
    }

    t1->timestamp -= t2->timestamp;
    time_setFromTimestamp(t1);
}


void time_set(struct time *t)
{
    t->timestamp = t->millis +
        1000 * (t->seconds + 60 * (t->minutes + 60 * t->hours));
}

void time_setFromTimestamp(struct time *t)
{
    uint32_t timestamp = t->timestamp;
    t->hours = timestamp / (1000UL * 60 * 60);
    timestamp -= t->hours * (1000UL * 60 * 60);

    t->minutes = timestamp / (1000UL * 60);
    timestamp -= t->minutes * (1000UL * 60);

    t->seconds = timestamp / (1000UL);
    timestamp -= t->seconds * (1000UL);

    t->millis = timestamp;
}

void time_format(const struct time *t, char *buffer)
{
    //uint8_t tenths = (t->millis+50) / 100;
    uint8_t seconds = t->seconds;
    uint8_t minutes = t->minutes;
    uint8_t hours = t->hours;

    /*if(tenths == 10) {
        tenths = 0;
        seconds++;
        if(seconds == 60) {
            seconds = 0;
            minutes++;
            if(minutes == 60) {
                minutes = 0;
                hours++;
            }
        }
    }*/
    sprintf(buffer, "%01u:%02u:%02u",
        hours, minutes, seconds);
}










