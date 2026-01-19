#include "ShiftReg.hpp"
#include "Pin.hpp"

#include <avr/cpufunc.h>
#include <stddef.h>

#define WAIT for (int i = 0; i < 5; i++) {\
                _NOP(); \
             }

ShiftReg::ShiftReg(Pin ser, Pin srck, Pin rck):
    dat(ser),
    srclk(srck),
    rclk(rck)
{}

ShiftReg::ShiftReg(const ShiftReg& sr):
    dat(sr.dat),
    srclk(sr.srclk),
    rclk(sr.rclk)
{}

void ShiftReg::operator<<(size_t n) {
    for (size_t i = 0; i < n; i++) {
        srclk.setState(true);
        WAIT
        srclk.setState(false);
        WAIT
    }

    rclk.setState(true);
    WAIT
    rclk.setState(false);
    WAIT
}

void ShiftReg::operator<<=(uint8_t x) {
    for (size_t i = 8; i > 0; i--) {
        uint8_t b = x & (1 << (i - 1));

        dat.setState(b);

        WAIT

        srclk.setState(true);
        WAIT
        srclk.setState(false);
        WAIT
    }

    rclk.setState(true);
    WAIT
    rclk.setState(false);
    WAIT
}

void ShiftReg::clear() {
    *this << 8;
}
