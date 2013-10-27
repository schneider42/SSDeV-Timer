#include "fonts/8x14_horizontal_LSB_1.h"
//#include "fonts/12x16_horizontal_LSB_1.h"
#include "lcd.h"

#include <stdbool.h>
#include <stdint.h>

#include <avr/pgmspace.h>

//#include "terminal_handler.h"

void font_render(uint8_t c, uint8_t x0, uint8_t y0)
{
    //const uint8_t *data = font[c];
    uint8_t x,y,byte,bit;
    
    //byte=0;
    uint8_t x_bytes = (SIZE_X - 1) / 8;
    uint8_t x_offset = 0;
    for(y = 0; y < SIZE_Y; y++) {
        for(x = 0; x < SIZE_X; x++) {
            byte = x_offset + (SIZE_X - x - 1) / 8;
            bit = (1 << ((SIZE_X + x) % 8));
            //terminal_printf("%u %u\n", byte, bit);
            if(pgm_read_byte(&font[c][byte]) & bit) {
                lcd_setPixel(x0 + x, y0 + y, true);
            } else {
                lcd_setPixel(x0 + x, y0 + y, false);
            }
        }
        x_offset += x_bytes + 1;
    }
}

void font_renders(char *s, uint8_t x0, uint8_t y0)
{
    while(*s){
        font_render(*s++, x0, y0);
        x0 += SIZE_X;
    }
}



