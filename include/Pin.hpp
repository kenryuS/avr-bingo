#ifndef __PIN_HPP__
#define __PIN_HPP__

#include <stdint.h>

#define PORTA_P (uint8_t*)(0x39)
#define PORTB_P (uint8_t*)(0x36)

class Pin {
    public:
        Pin(uint8_t* pt, uint8_t pn);
        Pin(const Pin& p);
        Pin(const Pin&& p) noexcept;

        ~Pin() = default;

        Pin& operator=(const Pin& p);

        void setPort(uint8_t* prt);
        uint8_t* getPort();

        void setPin(uint8_t pn);
        uint8_t getPin();

        bool getState();
        void setState(bool x);

    private:
        uint8_t* port;
        uint8_t pin;
};

#endif // __PIN_HPP__
