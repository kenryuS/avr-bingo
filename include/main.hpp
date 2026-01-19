#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <stdint.h>
#include "Pin.hpp"
#include "ShiftReg.hpp"

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

typedef struct {
    ShiftReg* sr;
    uint8_t n;
    bool inHex;
    bool digit;
} DispParam;

void displayT_CB(DispParam* dp, int*);
void blinkT_CB(Pin* p, int*);

void setup(void);

int main(void);

#endif // __MAIN_HPP__
