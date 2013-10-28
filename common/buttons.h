#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>

struct button_press {
    uint32_t timestamp;
    uint8_t button;
}__attribute__((packed));

#define BUTTONS_COUNT 15

void buttons_init(void);
uint32_t buttons_getPressed(void);
void buttons_tick(void);

#endif
