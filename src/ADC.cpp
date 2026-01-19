#include "ADC.hpp"
#include "defs.hpp"

#include <stdint.h>

#include <avr/io.h>

ADC::ADC(enum ADC::VRef vr):
    vref(vr)
{
    switch (vref) {
        case (ADC::vref_vcc):
            ADMUX = 0x00;
            break;
        case (ADC::vref_aref):
            ADMUX = 0x40;
            break;
        case (ADC::vref_11):
            ADMUX = 0x80;
            break;
    }

    ADCSRA |= (1 << )
    ADCSRB &= ~(1 << ADLAR); // right adjusted

}
