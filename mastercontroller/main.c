#include "timer1.h"
#include "mastercontroller.h"

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

int main(void)
{
    wdt_disable();
    /* Clear WDRF in MCUSR */
    MCUSR &= ~(1<<WDRF);
    /* Write logical one to WDCE and WDE */
    /* Keep old prescaler setting to prevent unintentional time-out */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Turn off WDT */
    WDTCSR = 0x00;
    
    timer1_init();
    sei();
    
    mastercontroller_init();
   
    while( 1 ){
        if( timer1_timebase ){
            timer1_timebase = 0;
            mastercontroller_tick();
        }
        mastercontroller_process();
    }
}

