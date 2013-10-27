#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>

void buttons_init(void);
uint32_t buttons_getPressed(void);
void buttons_tick(void);

#endif
