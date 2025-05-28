// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdint.h>

// Visual Studio debug/release branch
#if defined(_DEBUG)
    constexpr bool JK_DEBUG = true;
    #define JK_EXCEPT_MODE = noexcept(false)
#elif defined(_NDEBUG)
    constexpr bool JK_DEBUG = false;
    #define JK_EXCEPT_MODE = noexcept(true)
#else
    #error "Go use Visual Studio"
#endif