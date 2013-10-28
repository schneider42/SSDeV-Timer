#include "sort.h"

#include <stdint.h>
#include <stdbool.h>

void sort(void **list,
            bool (*gt)(void *, void*), uint16_t n)
{
    uint16_t i, j;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(gt(list[j], list[j + 1])) {
                void *tmp = list[j + 1];
                list[j + 1] = list[j];
                list[j] = tmp;
            }
        }
    }
}

