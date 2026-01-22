#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <stdint.h>
#include <stddef.h>

#include "Pin.hpp"
#include "ADC.hpp"

using VirtualButtonStateChangeInterruptVect = void(bool, void*, void*);

inline void EMPTY_VBSCIV(bool, void*, void*) {
    return;
}

class Button {
    public:
        Button(VirtualButtonStateChangeInterruptVect v, void* arg, void* res);
        Button(const Button&) = delete;
        constexpr Button(Button&& b) noexcept;

        void setState(bool s);
        bool getState();

        void checkAndInterrupt();
    private:
        bool currentState;
        bool lastState;
        VirtualButtonStateChangeInterruptVect* vect;
        void* argValPtr;
        void* retValPtr;
};

// Buttons with digital to analog converter, without multi-button detection
class DACButtons {
    public:
        DACButtons(ADCC* adc, enum ADCC::Channel ch, size_t num, uint8_t* map, uint8_t margin, Button* btns);
        DACButtons(const DACButtons&) = delete;
        DACButtons(const DACButtons&&) = delete;

        size_t getButtonNum();
        Button* getButtons();

        bool getState(size_t index);
    private:
        ADCC* dac;
        enum ADCC::Channel channel;
        size_t buttonNum;
        uint8_t dacMargin;
        uint8_t* dacMapping;
        Button* buttons;
};

#endif // __BUTTON_HPP__
