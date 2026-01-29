#ifndef __TIMER__HPP__
#define __TIMER__HPP__

#include "defs.hpp"

/*! Macros refered from Arduino's implementation. */
#define clockCyclesPerMicrosecond (F_CPU / 1000000L)
/*! Macros refered from Arduino's implementation. */
#define clockCyclesToMicroseconds(a) ((a) / clockCyclesPerMicrosecond)
/*! Macros refered from Arduino's implementation. */
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64*256))
/*! Macros refered from Arduino's implementation. */
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

/*! Function signiture for timer's callback @see Timer. */
template<typename Arg, typename Res>
using Callback = void(Arg*, Res*);

/*! Setup 8-bit timer 0 with appropriate register setting. */
void timerSetup(void);

/*! refered from Arduino's implementation */
unsigned long millis(void);

#include "Timer.tpp"

#endif // __TIMER__HPP__
