#ifndef __SHIFT_REG_HPP__
#define __SHIFT_REG_HPP__

#include <stdint.h>
#include <stddef.h>

#include "Pin.hpp"

/*! Shift Register Class.
 * This class represents 74HC595 shift register.
 */
class ShiftReg {
    public:
        /*! Constructor.
         * @param ser Pin connected to serial data input of a register.
         * @param srck Pin connected to shift clock of a register.
         * @param rck Pin connected to output latch of a register.
         */
        ShiftReg(Pin ser, Pin srck, Pin rck);
        /*! Copy Constructor. */
        ShiftReg(const ShiftReg& sr);
        ShiftReg(const ShiftReg&& sr) = delete;

        /*! Destructor. */
        ~ShiftReg() = default;

        /*! Operator that performs arbitary number of shifting.
         * @param n Number of shiftings.
         */
        void operator<<(size_t n);
        /*! Loads 8-bit value to a register.
         * @param x 8-bit value to be loaded.
         */
        void operator<<=(uint8_t x);

        /*! shift out all data with 0. */
        void clear();
    private:
        Pin dat;
        Pin srclk;
        Pin rclk;
};

#endif // __SHIFT_REG_HPP__
