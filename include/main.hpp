#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <stdint.h>
#include "Pin.hpp"
#include "ShiftReg.hpp"
#include "Button.hpp"
#include "u80.hpp"

using uint80_t = U80;

static const uint8_t NUMS[16] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111,
    0b01110111,
    0b01111100,
    0b00111001,
    0b01011110,
    0b01111001,
    0b01110001
};

static uint8_t DACBTNMAPPING[4] = {
    6,
    12
};

/*! @enum BingoMachineError
 * @brief Error codes of bingo machine.
 */
typedef enum {
    SUCCESS, /*! Interrupt is successfully exited. */
    ALL_NUMBER_CALLED, /*! All of numbers has been called out, requires parameters reset. */
    FAILED_TO_CALL_NUMBER /*! Could not call out number. */
} BingoMachineError;

/*! @struct DispParam
 * @brief Parameters for 7 segments display.
 */
typedef struct {
    ShiftReg* sr; /*! Pointer to shift register object @see ShiftReg. */
    uint8_t n; /*! Number to be displayed. */
    bool inHex; /*! Whether to display number as hexadecimal. */
    bool omitTensZero; /*! Whether to omit tens zero when displaying single digit number */
    bool digit; /*! digit to be shown. Tens for true and ones for false. */
} DispParam;

/*! @struct CallOutNumberParam
 * @brief Parameters for calling out numbers.
 */
typedef struct {
    uint8_t* n; /*! Current called number. */
    BingoMachineError retCode; /*! Return code of interrupt @see callOutNumber_VECT. */
    uint80_t calledNums; /*! uint80_t that manages called numbers @see U80. */
} CallOutNumberParam;

/*! Callback function for displaying number to 7 segments display.
 * @param dp Pointer to display parameters @see DispParam.
 */
void displayT_CB(DispParam* dp, int*);
/*! Callback function for scanning button states.
 * @param d Pointer to DAC buttons @see DACButtons.
 */
void buttonT_CB(DACButtons* d, int*);

/*! Interrupt vector for calling out number.
 * @param s current state of button.
 * @param arg Pointer to parameters for calling out number @see CallOutNumberParam.
 */
void callOutNumber_VECT(bool s, void* arg, void*);
/*! Interrupt vector for reseting parameters.
 * @param s current state of button.
 * @param arg Pointer to parameters for calling out number @see CallOutNumberParam.
 */
void resetBingo_VECT(bool s, void* arg, void*);

/*! Setups microcontroler ports, timer, and random number generator. */
void setup(void);

/*! Main entry point of a bingo machine. */
int main(void);

#endif // __MAIN_HPP__
