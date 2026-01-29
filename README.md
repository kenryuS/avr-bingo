# AVR Bingo Machine

## Circuitry

There are three "modules" consisting the bingo machine: multiplexed 7 segments display with 8 bits shift register, 4 buttons with RC low pass filter-schmitt inverter de-bouncing, and 4 bits R-2R ladder DAC.

The 8 bits shift register cuts the 8 pins (7 pins for each segments + 1 display selector pin) down to 3 pins. 4 bits R-2R ladder DAC also contributes to pin number reduction by condensing 4 inputs into single output.

This machine uses Attiny 44A-PU but theoretically other 8 pins DIP AVR microcontroller such as Attiny85-20PU can be used due to small pin number requirement.

## Implementation

Even though I specified C++ 20 for language standard, AVR microcontrollers lack standard C++ libraries, so no fancy stuffs like lambda functions, array class, smart pointers, and many other utility functions were available.
Also the use of templates is limited and still relies on void pointers in some code.
Despite being the "simple" bingo machine, these problem bloated the codebase more than I expected; with more than 500 lines of code just for implementations.

