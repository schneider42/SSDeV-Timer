#ifndef TIME_PROCESS_H_
#define TIME_PROCESS_H_
#include "time.h"

void time_init(void);
void time_tick(void);
struct time* time_getTime(void);

#endif
