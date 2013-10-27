#include "buttons.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stddef.h>

#include <stdbool.h>

#define BUTTONS_COUNT 15
#define BUTTONS_MAX_COUNT 32
#define DEADTIME 10

struct button {
    char port;
    uint8_t pin;
    uint8_t deadtime;
    bool pressed;
    bool changed;
};

struct button buttons[] = {
    {'C', 0}, {'C', 1}, {'C', 6}, {'C', 7},
    {'A', 7}, {'A', 6}, {'A', 5}, {'A', 4},
    {'A', 3}, {'A', 2}, {'A', 1}, {'A', 0},
    {'B', 2}, {'D', 7}, {'D', 6}
};

struct button *buttons_lookup[BUTTONS_MAX_COUNT];

uint16_t buttons_deadtime[BUTTONS_COUNT];

static void process_change(struct button *b, uint8_t value)
{
    if(value == 0 && !b->pressed && b->deadtime == 0) {
        b->pressed = true;
        b->deadtime = DEADTIME;
        b->changed = true;
    }

    if(value && b->pressed && b->deadtime == 0) {
        b->pressed = false;
        b->deadtime = DEADTIME;
    }
}

static inline void check_change(uint8_t port,
        uint8_t now, uint8_t prev)
{
    uint8_t i;
    struct button *b;
    uint8_t change = now ^ prev;

    for(i = 0; i < 8; i++) {
        if(change & (1 << i)) {
            b = buttons_lookup[port * 8 + i];
            if(b) {
                process_change(b, now & (1 << i));
            }
        }
    }
}

ISR(PCINT0_vect)
{
    static uint8_t prev = 0xFF;
    PCIFR |= (1 << PCIF0);
    uint8_t now = PINA;
    check_change(0, now, prev);
    prev = now;
}

ISR(PCINT1_vect)
{
    static uint8_t prev = 0xFF;
    PCIFR |= (1 << PCIF1);
    uint8_t now = PINB;
    check_change(1, now, prev);
    prev = now;
}

ISR(PCINT2_vect)
{
    static uint8_t prev = 0xFF;
    PCIFR |= (1 << PCIF2);
    uint8_t now = PINC;
    check_change(2, now, prev);
    prev = now;
}

ISR(PCINT3_vect)
{
    static uint8_t prev = 0xFF;
    PCIFR |= (1 << PCIF3);
    uint8_t now = PIND;
    check_change(3, now, prev);
    prev = now;
}

void buttons_enableInterrupt(struct button b)
{
    uint8_t x = b.port;
    if(x == 0) {
        PCMSK0 |= (1 << b.pin);
    } else if(x == 1) {
        PCMSK1 |= (1 << b.pin);
    } else if(x == 2) {
        PCMSK2 |= (1 << b.pin);
    } else if(x == 3) {
        PCMSK3 |= (1 << b.pin);
    }
}

void buttons_init(void)
{
    uint8_t i;
    for(i = 0; i < BUTTONS_MAX_COUNT; i++) {
        buttons_lookup[i] = NULL;
    }

    for(i = 0; i < BUTTONS_COUNT; i++) {
        buttons[i].deadtime = 0;
        buttons[i].port -= 'A';
        buttons[i].pressed = false;
        buttons[i].changed = false;

        switch(buttons[i].port) {
            case 0:
                DDRA &= ~(1 << buttons[i].pin);
                PORTA |= (1 << buttons[i].pin);
            break;
            case 1:
                DDRB &= ~(1 << buttons[i].pin);
                PORTB |= (1 << buttons[i].pin);
            break;
            case 2:
                DDRC &= ~(1 << buttons[i].pin);
                PORTC |= (1 << buttons[i].pin);
            break;
            case 3:
                DDRD &= ~(1 << buttons[i].pin);
                PORTD |= (1 << buttons[i].pin);
            break;
        }
        
        uint8_t n = buttons[i].port * 8 + buttons[i].pin;
        buttons_lookup[n] = &buttons[i];
        
        buttons_enableInterrupt(buttons[i]);
    }

    PCICR |= (1 << PCIE0) | (1 << PCIE1) | (1 << PCIE2) | (1 << PCIE3);
}

uint32_t buttons_getPressed(void)
{
    uint8_t i;
    uint32_t res = 0;
    for(i = 0; i < BUTTONS_COUNT; i++) {
        // This slight race condition is OK
        // If a user presses the button at this
        // exact time, it should be ignored anyway.
        if(buttons[i].changed) {
            buttons[i].changed = false;
            res |= (1UL << i); 
        }
    }
    return res;
}

void buttons_tick(void)
{
    uint8_t i;
    for(i = 0; i < BUTTONS_COUNT; i++) {
        cli();
        if(buttons[i].deadtime) {
            buttons[i].deadtime--;
        }
        sei();
    }
}









