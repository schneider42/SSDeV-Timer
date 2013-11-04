#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

struct time {
    uint32_t timestamp;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t millis;
};

void time_clear(struct time *t);
void time_add(struct time *t1, const struct time *t2);
void time_set(struct time *t);
void time_setFromTimestamp(struct time *t);
void time_format(const struct time *t, char *buffer);
void time_subtract(struct time *t1, const struct time *t2);

#endif
