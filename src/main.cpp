#include "main.hpp"

#include "defs.hpp"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "Pin.hpp"
#include "ShiftReg.hpp"
#include "Timer.hpp"
#include "ADC.hpp"

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

void readADCT_CB(ADCC* a, uint8_t* n) {
    uint32_t x = a->read(ADCC::channel_3);
    x = (100 * x) / 1024;
    *n = (uint8_t)x;
}

void setup(void) {
    DDRA = 0x07;
    PORTA = 0x00;
    timerSetup();
}

int main(void) {
    setup();

    ADCC adc(ADCC::vref_vcc);

    Pin ser(PORTA_P, PINA0);
    Pin srclk(PORTA_P, PINA2);
    Pin rclk(PORTA_P, PINA1);

    ShiftReg sr(ser, srclk, rclk);
    sr.clear();

    DispParam dp = {
        .sr = &sr,
        .n = 0,
        .inHex = false,
        .digit = false
    };
    Timer<DispParam, int> displayT(displayT_CB, &dp, 0, 1);
    Timer<ADCC, uint8_t> readADCT(readADCT_CB, &adc, &(dp.n), 100);

    while (1) {
        displayT.tick();
        readADCT.tick();
    }
}
