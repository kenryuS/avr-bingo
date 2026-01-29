#include "main.hpp"
#include "defs.hpp"

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "Pin.hpp"
#include "ShiftReg.hpp"
#include "Timer.hpp"
#include "ADC.hpp"
#include "Button.hpp"
#include "u80.hpp"

using uint80_t = U80;

void displayT_CB(DispParam* dp, int*) {
    uint8_t d = 0;
    uint8_t data = 0;

    if (dp->digit) {
        if (dp->inHex) {
            d = dp->n / 0x10;
        } else {
            d = dp->n / 10;
        }
        if (dp->omitTensZero && (d == 0)) {
            data = 0x00;
        } else {
            data = NUMS[d];
        }
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

void callOutNumber_VECT(bool s, void* arg, void*) {
    if (!s) return;

    CallOutNumberParam* param = (CallOutNumberParam*)arg;
    if (param->calledNums == "07FFFFFFFFFFFFFFFFFF"_xU80) {
        param->retCode = ALL_NUMBER_CALLED;
        return;
    }

    uint8_t idx = 0;
    uint16_t itr = 0;
    bool isAvailable = false;
    const uint16_t MAX_ITR = (uint16_t)1 << 15;

    while (itr < MAX_ITR) {
        idx = (uint8_t)(rand() % 75);
        isAvailable = !((param->calledNums)[idx]);
        if (isAvailable) {
            *(param->n) = idx + 1;
            param->calledNums.toggle(idx);
            param->retCode = SUCCESS;
            return;
        }
        itr++;
    }

    param->retCode = FAILED_TO_CALL_NUMBER;
    return;
}

void resetBingo_VECT(bool s, void* arg, void*) {
    if (!s) return;
    CallOutNumberParam* param = (CallOutNumberParam*)arg;
    param->calledNums = "00000000000000000000"_xU80;
    param->retCode = SUCCESS;
    *(param->n) = 0;
}

void setup(void) {
    DDRA = 0x87;
    PORTA = 0x00;
    DDRB = 0x01;
    PORTB = 0x00;
    timerSetup();
    ADMUX = 0xA2;
    ADCSRA |= 0x04;
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC)) {;;}
    srand(ADC);
}

int main(void) {
    setup();

    Pin statusLED(PORTB_P, PINB0);

    ADCC adc(ADCC::vref_vcc);

    ShiftReg sr(Pin(PORTA_P, PINA0), Pin(PORTA_P, PINA2), Pin(PORTA_P, PINA1));
    sr.clear();

    DispParam dp = {
        .sr = &sr,
        .n = 0,
        .inHex = false,
        .omitTensZero = true,
        .digit = false
    };

    uint8_t calledNumber = 0;
    CallOutNumberParam bingo = {
        .n = &calledNumber,
        .retCode = SUCCESS,
        .calledNums = "00000000000000000000"_xU80
    };

    Button btns[2] = {
        Button(callOutNumber_VECT, &bingo, 0),
        Button(resetBingo_VECT, &bingo, 0),
    };

    DACButtons dacb(&adc, ADCC::channel_3, 2, DACBTNMAPPING, 2, btns);

    Timer<DispParam, int> displayT(displayT_CB, &dp, 0, 1);
    Timer<DACButtons, int> buttonT(buttonT_CB, &dacb, 0, 10);

    while (1) {
        displayT.tick();
        buttonT.tick();

        if (bingo.retCode != SUCCESS) {
            dp.n = (uint8_t)(bingo.retCode) + 0xE0;
            dp.inHex = true;
            statusLED.setState(true);
        } else {
            dp.n = calledNumber;
            dp.inHex = false;
            statusLED.setState(false);
        }
    }
}
