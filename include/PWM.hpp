#ifndef __PWM_HPP__
#define __PWM_HPP__

#include <stdint.h>

// abstracts 16 bit timer 1 in phase correct 10 bits PWM mode
class PWM {
    public:
        enum channel {
            channelA,
            channelB
        };

        PWM(enum PWM::channel c, uint16_t d = 0, uint16_t scale);
        PWM(const PWM&) = delete;
        PWM(const PWM&&) = delete;

        void setDuty(uint16_t d);
        uint16_t getDuty();
    private:
        uint16_t duty;
};

#endif // __PWM_HPP__
