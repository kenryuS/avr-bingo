#ifndef __TIMER__HPP__
#define __TIMER__HPP__

#include "defs.hpp"

#include <avr/interrupt.h>
#include <avr/io.h>

#define clockCyclesPerMicrosecond (F_CPU / 1000000L)
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond)

#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64*256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

template<typename Arg, typename Res>
using Callback = void(Arg*, Res*);

void timerSetup(void);
unsigned long millis(void);

#include "Timer.tpp"

#endif // __TIMER__HPP__
