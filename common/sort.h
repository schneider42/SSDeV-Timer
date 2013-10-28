#ifndef SORT_H_
#define SORT_H_

#include <stdint.h>
#include <stdbool.h>

void sort(void **list,
            bool (*lt)(void *, void*), uint16_t n);

#endif
