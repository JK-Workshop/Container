// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_INDEX_HEAP)
#define JK_INDEX_HEAP

#include <stdint.h>
#include <algorithm>

namespace JK {

	enum class IHeapImpl : uint32_t {
		COSTUM_IMPL          = 0,
		BINARY_HEAP          = 1,
		FIBONACCI_HEAP       = 2
	};

	enum class IHeapErr : uint32_t {
		IHEAP_SUCCESS         = 0,
		IHEAP_EMPTY           = 1,
		IHEAP_FULL            = 2,
		IHEAP_VALUE_NOT_FOUND = 3
	};

	template<uint32_t HEAP_S, class COMPARE_T, IHeapImpl IMPLEMENTATION>
	class IndexHeap {};
}

#include "BinaryHeap.h"
#include "FibonacciHeap.h"

#endif // JK_INDEX_HEAP