#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <stdint.h>
#include <stddef.h>

#include "Pin.hpp"
#include "ADC.hpp"

/*! Function signiture for constructing virtual interrupt vector @see Button. */
using VirtualButtonStateChangeInterruptVect = void(bool, void*, void*);

/*! Empty virtual button state change interrupt vector function.
 * The placeholder function for Buttons' interrupt @see Button.
 */
inline void EMPTY_VBSCIV(bool, void*, void*) {
    return;
}

/*! Button class.
 * This class manages single button state and execution of virtual interrupt or callback.
 */
class Button {
    public:
        /*! Constructor.
         * @param v virtual interrupt vector or callback to be executed.
         * @param arg void pointer to interrupt argument(s).
         * @param res void pointer to interrupt return(s).
         */
        Button(VirtualButtonStateChangeInterruptVect v, void* arg, void* res);
        Button(const Button&) = delete;
        /*! Move constructor. */
        constexpr Button(Button&& b) noexcept;

        /*! Sets state of button.
         * Usually for counteracting pull up.
         * @param s State of button represented in boolean.
         */
        void setState(bool s);
        /*! Gets state of button. */
        bool getState();

        /*! Check state and execute interrupt.
         * The interrupt is only executed when current and previous state missmatches.
         */
        void checkAndInterrupt();
    private:
        bool currentState;
        bool lastState;
        VirtualButtonStateChangeInterruptVect* vect;
        void* argValPtr;
        void* retValPtr;
};

/** DAC buttons class.
 * Buttons with digital to analog converter, without multi-button detection.
 */
class DACButtons {
    public:
        /*! Constructor.
         * @param adc ADC to read value from DAC.
         * @param ch ADC channel to read from.
         * @param num Number of buttons to handel.
         * @param map Map of DAC value in percentage to buttons.
         * @param margin Margin of DAC value.
         * @param btns Array of buttons @see Button.
         */
        DACButtons(ADCC* adc, enum ADCC::Channel ch, size_t num, uint8_t* map, uint8_t margin, Button* btns);
        DACButtons(const DACButtons&) = delete;
        DACButtons(const DACButtons&&) = delete;

        /*! Gets number of buttons. */
        size_t getButtonNum();
        /*! Gets array of buttons. */
        Button* getButtons();

        /*! Gets state of specified button.
         * @param index Index in buttons array.
         * @return Current state of the button.
         */
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
