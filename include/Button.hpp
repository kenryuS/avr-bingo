#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <cstdint>
#include "Pin.hpp"

class Button {
    public:
        Button(uint8_t* port, uint8_t pin, bool pullup);
        Button(Pin& p, bool pullup);
        Button(const Button& b);
        Button(const Button&& b) = delete;

        bool getState();
    private:
        Pin buttonPin;
        bool isPulledUp;
        unsigned long lastDebounce;
};

#endif // __BUTTON_HPP__
