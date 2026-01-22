#include "main.hpp"

#include "defs.hpp"

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stddef.h>

#include "Pin.hpp"
#include "ShiftReg.hpp"
#include "Timer.hpp"
#include "ADC.hpp"
#include "Button.hpp"

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

void buttonT_CB(DACButtons* d, int*) {
    size_t bn = d->getButtonNum();
    for (size_t i = 0; i < bn; i++) {
        if (d->getState(i)) {
            ((d->getButtons())[i]).checkAndInterrupt();
        }
    }
}

void setup(void) {
    DDRA = 0x07;
    PORTA = 0x00;
    timerSetup();
}

int main(void) {
    setup();

    ADCC adc(ADCC::vref_vcc);


    Button btns[4] = {
        Button(EMPTY_VBSCIV, 0, 0),
        Button(EMPTY_VBSCIV, 0, 0),
        Button(EMPTY_VBSCIV, 0, 0),
        Button(EMPTY_VBSCIV, 0, 0)
    };

    DACButtons dacb(
        &adc,
        ADCC::channel_3,
        4,
        DACBTNMAPPING,
        2,
        btns
    );

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
    Timer<DACButtons, int> buttonT(buttonT_CB, &dacb, 0, 10);

    while (1) {
        displayT.tick();
        buttonT.tick();
    }
}
