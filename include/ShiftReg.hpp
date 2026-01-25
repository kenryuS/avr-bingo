#ifndef __SHIFT_REG_HPP__
#define __SHIFT_REG_HPP__

#include <stdint.h>
#include <stddef.h>

#include "Pin.hpp"

class ShiftReg {
    public:
        ShiftReg(Pin ser, Pin srck, Pin rck);
        ShiftReg(const ShiftReg& sr);
        ShiftReg(const ShiftReg&& sr) = delete;

        ~ShiftReg() = default;

        void operator<<(size_t n); // shift contents n times
        void operator<<=(uint8_t x); // load 8 bit data to register

        // shift out all data with 0
        void clear();
    private:
        Pin dat;
        Pin srclk;
        Pin rclk;
};

#endif // __SHIFT_REG_HPP__
