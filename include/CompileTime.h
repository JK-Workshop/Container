// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <type_traits>
#include <utility>

// Visual Studio debug/release branch
#define JK_DEBUG_BREAK __debugbreak();
#if defined(_DEBUG)
#	include <assert.h>
constexpr bool JK_DEBUG = true;
#	define JK_VERIFY(CONDITION, MESSAGE) assert(CONDITION, MESSAGE)
#elif defined(NDEBUG)
#   if defined(JK_BENCHMARK)
#		include "Timer.h"
#		define JK_SET_TIMER(TIMER_INSTANCE)
#		define JK_LAP_TIMER(TIMER_INSTANCE)
#		define JK_PAUSE_TIMER(TIMER_INSTANCE)
#		define JK_END_TIMER(TIMER_INSTANCE)
#   else
#		define JK_SET_TIMER(TIMER_INSTANCE)
#		define JK_LAP_TIMER(TIMER_INSTANCE)
#		define JK_PAUSE_TIMER(TIMER_INSTANCE)
#		define JK_END_TIMER(TIMER_INSTANCE)
#   endif
constexpr bool JK_DEBUG = false;
#define JK_VERIFY(CONDITION, MESSAGE)
#else
#endif