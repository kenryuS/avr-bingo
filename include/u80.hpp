#ifndef __U80_HPP__
#define __U80_HPP__

#include <stdint.h>
#include <stddef.h>

// virtual unsigned 80 bit wide integer
class U80 {
    public:
        U80() = default;
        constexpr U80(uint16_t x[5]);
        U80(const U80& x); // copy
        U80(U80&& x); 

        ~U80() = default;

        U80& operator=(const U80& other); // copy
        U80& operator=(U80&& other); // move

        constexpr U80 operator~();
        bool operator[](const size_t n); // bit access
        bool operator==(const U80& rhs);
        bool operator!=(const U80& rhs);

        void toggle(const size_t n); // toggle n-th bit
    private:
        uint16_t val[5]; // 16 * 5 = 80
};

// convert string hexadecimal representation of "uint80_t" into U80 object
// eg. "AA998877665544332211"_u80 is { 0xAA99, 0x8877, 0x6655, 0x4433, 0x2211 }
U80 operator""_xU80(const char* x, size_t sz);

#endif // __U80_HPP__
