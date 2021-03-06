#ifndef TIME_PROCESS_H_
#define TIME_PROCESS_H_
#include "time.h"

void time_init(void);
void time_tick(void);
struct time* time_getTime(void);
void time_setTime(const struct time *time);
void time_stop(void);
void time_start(void);
#endif
