#ifndef __PIN_HPP__
#define __PIN_HPP__

#include <stdint.h>

/** Pointer to PORTA register in Attiny44a. */
#define PORTA_P (uint8_t*)(0x39)
/** Pointer to PORTB register in Attiny44a. */
#define PORTB_P (uint8_t*)(0x36)

/** Pin class.
 * This class represents a pin of microcontroler by specifying port and pin.
 */
class Pin {
    public:
        /** Constructor.
         * @param pt Pointer to port register.
         * @param pn Pin index.
         */
        Pin(uint8_t* pt, uint8_t pn);
        /** Copy constructor */
        Pin(const Pin& p);
        /** Move constructor.
         * Behaves same as copy constructor @see Pin(const Pin& p).
         */
        Pin(const Pin&& p) noexcept;

        /** Destructor */
        ~Pin() = default;

        /** Copy assignment */
        Pin& operator=(const Pin& p);

        /** Sets port address.
         * @param prt Pointer to port.
         */
        void setPort(uint8_t* prt);
        /** Gets port address. */
        uint8_t* getPort();

        /** Sets pin index.
         * @param pn Index of a pin.
         */
        void setPin(uint8_t pn);
        /** Gets pin index. */
        uint8_t getPin();

        /** Gets digital state of a pin. */
        bool getState();
        /** Sets digital state of a pin.
         * @param x Target state of a pin.
         */
        void setState(bool x);

    private:
        uint8_t* port;
        uint8_t pin;
};

#endif // __PIN_HPP__
