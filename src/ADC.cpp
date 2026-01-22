#include "ADC.hpp"
#include "defs.hpp"

#include <stdint.h>

#include <avr/io.h>

ADCC::ADCC(enum ADCC::VRef vr):
    vref(vr)
{
    switch (vref) {
        case (ADCC::vref_vcc):
            ADMUX = 0x00;
            break;
        case (ADCC::vref_aref):
            ADMUX = 0x40;
            break;
        case (ADCC::vref_11):
            ADMUX = 0x80;
            break;
    }

    ADCSRA |= 0x04; // prescale 16
    ADCSRA |= (1 << ADEN);
}

void ADCC::setVRef(enum ADCC::VRef vr) {
    switch (vr) {
        case (ADCC::vref_vcc):
            ADMUX &= ~(1 << 7);
            ADMUX &= ~(1 << 6);
            break;
        case (ADCC::vref_aref):
            ADMUX &= ~(1 << 7);
            ADMUX |= (1 << 6);
            break;
        case (ADCC::vref_11):
            ADMUX |= (1 << 7);
            ADMUX &= ~(1 << 6);
    }
}

enum ADCC::VRef ADCC::getVRef() {
    return vref;
}

void ADCC::setChannel(enum ADCC::Channel c) {
    uint8_t x = (uint8_t)c;

    ADMUX &= ~(0x3F);
    ADMUX |= x;
}

enum ADCC::Channel ADCC::getChannel() {
    return ch;
}

uint16_t ADCC::read(enum ADCC::Channel c) {
    this->setChannel(c);

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC)) {
        ;;
    }

    return ADC;
}
