#include "Timer.hpp"

#include <avr/io.h>

volatile unsigned long timer0_millis = 0;
volatile unsigned long timer0_overflow_count = 0;

ISR(TIM0_OVF_vect) {
    unsigned long m = timer0_millis;

    m += MILLIS_INC;

    timer0_millis = m;
    timer0_overflow_count++;
}

void timerSetup(void) {
    sei();

    TCCR0A = 0x00;
    TCCR0B = 0x03;
    TIMSK0 = 0x01;
}

unsigned long millis(void) {
    unsigned long m;
    uint8_t old_sreg = SREG;

    cli();
    m = timer0_millis;
    SREG = old_sreg;

    return m;
}

