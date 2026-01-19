#include "main.hpp"

#include "defs.hpp"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "Pin.hpp"
#include "ShiftReg.hpp"
#include "Timer.hpp"

void displayT_CB(DispParam* dp, int*) {
    uint8_t d = 0;
    uint8_t data = 0;

    if (dp->digit) {
        if (dp->inHex) {
            d = dp->n / 0x10;
        } else {
            d = dp->n / 10;
        }
        data = NUMS[d];
        data |= 0x80;
    } else {
        if (dp->inHex) {
            d = dp->n % 0x10;
        } else {
            d = dp->n % 10;
        }
        data = NUMS[d];
    }

    dp->digit = !(dp->digit);

    *(dp->sr) <<= data;
}

void blinkT_CB(Pin* p, int*) {
    p->setState(!(p->getState()));
}

void setup(void) {
    DDRB = 0x01;
    PORTB = 0x00;
    DDRA = 0x07;
    PORTA = 0x00;
    timerSetup();
}

int main(void) {
    setup();

    Pin ser(PORTA_P, PINA0);
    Pin srclk(PORTA_P, PINA2);
    Pin rclk(PORTA_P, PINA1);

    Pin led(PORTB_P, PINB0);

    ShiftReg sr(ser, srclk, rclk);
    sr.clear();

    DispParam dp = {
        .sr = &sr,
        .n = 0,
        .inHex = false,
        .digit = false
    };
    Timer<DispParam, int> displayT(displayT_CB, &dp, 0, 1000);

    Timer<Pin, int> blinkT(blinkT_CB, &led, 0, 1000);

    while (1) {
        //displayT.tick();
        blinkT.tick();
    }
}
