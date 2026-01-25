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
    12,
    24,
    50
};

typedef enum {
    SUCCESS,
    ALL_NUMBER_CALLED,
    FAILED_TO_CALL_NUMBER
} BingoMachineError;

typedef struct {
    ShiftReg* sr;
    uint8_t n;
    bool inHex;
    bool omitTensZero;
    bool digit;
} DispParam;

typedef struct {
    uint8_t* n;
    BingoMachineError retCode;
    uint80_t calledNums;
} CallOutNumberParam;

void displayT_CB(DispParam* dp, int*);
void buttonT_CB(DACButtons* d, int*);

void btn1_VECT(bool s, void* arg, void*);
void btn2_VECT(bool s, void* arg, void*);
void callOutNumber_VECT(bool s, void* arg, void*);
void resetBingo_VECT(bool s, void* arg, void*);

void setup(void);

int main(void);

#endif // __MAIN_HPP__
