#include "Button.hpp"
#include "ADC.hpp"

#include <stdint.h>
#include <stddef.h>


Button::Button(VirtualButtonStateChangeInterruptVect v, void* arg, void* res):
    vect(v),
    argValPtr(arg),
    retValPtr(res)
{
    currentState = false;
    lastState = false;
}

constexpr Button::Button(Button&& b) noexcept:
    currentState(b.currentState),
    lastState(b.lastState),
    vect(b.vect),
    retValPtr(b.retValPtr)
{}

void Button::setState(bool s) {
    lastState = currentState;
    currentState = s;
}

bool Button::getState() {
    return currentState;
}

void Button::checkAndInterrupt() {
    if (currentState != lastState) {
        (*vect)(currentState, argValPtr, retValPtr);
    }
}

DACButtons::DACButtons(ADCC* adc, enum ADCC::Channel ch, size_t num, uint8_t* map, uint8_t margin, Button* btns):
    dac(adc),
    channel(ch),
    buttonNum(num),
    dacMargin(margin),
    dacMapping(map),
    buttons(btns)
{}

size_t DACButtons::getButtonNum() {
    return buttonNum;
}

Button* DACButtons::getButtons() {
    return buttons;
}

bool DACButtons::getState(size_t index) {
    uint32_t dacRes = dac->read(channel);
    uint8_t x = (100 * dacRes) / 1024;
    if (x > (dacMapping[index] - dacMargin) && x < (dacMapping[index] + dacMargin)) {
        buttons[index].setState(true);
        return true;
    }

    buttons[index].setState(false);
    return false;
}
