#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdint.h>

struct button_press {
    uint32_t timestamp:24;
    uint8_t button:4;
    uint8_t table:4;
}__attribute__((packed));

#define BUTTONS_COUNT 15

#define BUTTON_1    (1<<12)
#define BUTTON_2    (1<<13)
#define BUTTON_3    (1<<14)

void buttons_init(void);
uint32_t buttons_getPressed(void);
void buttons_tick(void);

#endif
