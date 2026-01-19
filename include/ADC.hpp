#ifndef __ADC_HPP__
#define __ADC_HPP__

#include <stdint.h>

// Single Ended 10 bits ADC
class ADC {
    public:
        enum Channel {
            channel_0,
            channel_1,
            channel_2,
            channel_3,
            channel_4,
            channel_5,
            channel_6,
            channel_7
        };

        enum VRef {
            vref_vcc,
            vref_aref,
            vref_11
        }

        ADC(enum VRef vr);
        ADC(const ADC&) = delete;
        ADC(const ADC&&) = delete;

        void setVRef(enum VRef vr);
        enum VRef getVRef();

        void setChannel(enum Channel c);
        enum Channel getChannel();

        void read(enum Channel c); // blocking opreation

    private:
        enum Channel ch;
        enum VRef vref
        uint16_t val;
}

#endif // __ADC_HPP__
