// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdint.h>
#include <type_traits>

// Visual Studio debug/release branch
#if defined(_DEBUG)
    constexpr bool JK_DEBUG = true;
    #define JK_EXCEPT_MODE noexcept(false)
    #define JK_VERIFY(CONDITION, MESSAGE) assert(CONDITION, MESSAGE)
#elif defined(_NDEBUG)
#   if defined(JK_BENCHMARK)
        #include "Timer.h"
        #define JK_SET_TIMER(TIMER_INSTANCE)
        #define JK_LAP_TIMER(TIMER_INSTANCE)
        #define JK_PAUSE_TIMER(TIMER_INSTANCE)
        #define JK_END_TIMER(TIMER_INSTANCE)
#   else
        #define JK_SET_TIMER(TIMER_INSTANCE)
        #define JK_LAP_TIMER(TIMER_INSTANCE)
        #define JK_PAUSE_TIMER(TIMER_INSTANCE)
        #define JK_END_TIMER(TIMER_INSTANCE)
#   endif
    constexpr bool JK_DEBUG = false;
    #define JK_EXCEPT_MODE noexcept(true)
    #define JK_VERYFY(CONDITION, MESSAGE)
#else
    #error "Go use Visual Studio"
#endif