#ifndef __U80_HPP__
#define __U80_HPP__

#include <stdint.h>
#include <stddef.h>

/*! virtual unsigned 80 bit wide integer
 * The 80 bit integer is constructed with 5 16 bit integers.
 */
class U80 {
    public:
        /*! Default Constructor. */
        U80() = default;
        /*! Constructor.
         * @param x Array of 5 uint16_t representing the value.
         */
        constexpr U80(uint16_t x[5]);
        /*! Copy Constructor. */
        U80(const U80& x);
        /*! Move Constructor.
         * Same behaviour as copy constructor.
         */
        U80(U80&& x); 

        /*! Destructor. */
        ~U80() = default;

        /*! Copy Assignment. */
        U80& operator=(const U80& other);
        /*! Move Assignment.
         * Same behaviour as copy assignment.
         */
        U80& operator=(U80&& other);

        /*! Logical not operator. */
        constexpr U80 operator~();
        /*! Bit access operator.
         * @param n n-th bit in a number.
         * @return bit state represented as boolean.
         */
        bool operator[](const size_t n);
        /*! Equality operator. */
        bool operator==(const U80& rhs);
        /*! Inequality operator. */
        bool operator!=(const U80& rhs);

        /*! toggle n-th bit in a number.
         * @param n bit to be flipped.
         */
        void toggle(const size_t n); 
    private:
        uint16_t val[5]; // 16 * 5 = 80
};

/*! @fn U80 operator""_xU80(const char* x, size_t sz)
 * @brief convert string hexadecimal representation of "uint80_t" into U80 object
 * @param x hexadecimal represented string.
 * @param sz length of string.
 * @return converted unsigned 80 bit integer.
 */
// eg. "AA998877665544332211"_u80 is { 0xAA99, 0x8877, 0x6655, 0x4433, 0x2211 }
U80 operator""_xU80(const char* x, size_t sz);

#endif // __U80_HPP__
