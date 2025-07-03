// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_INDEX_HEAP)
#define JK_INDEX_HEAP

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

#include "CompileTime.h"

namespace JK {

	enum class IHeapImpl : uint32_t {
		COSTUM_IMPL    = 0,
		BINARY_HEAP    = 1,
		FIBONACCI_HEAP = 2
	};

	template<JK::UintFast_t auto HEAP_S, JK::IHeapImpl IMPLEMENTATION, class COMPARATOR_T>
	class IndexHeap {};
}

#include "IndexHeap/BinaryHeap.h"
#include "IndexHeap/FibonacciHeap.h"

#define indexHeap IndexHeap<HEAP_S, IMPLEMENTATION, COMPARATOR_T>

namespace JK {
	
	template<JK::UintFast_t auto HEAP_S, JK::IHeapImpl IMPLEMENTATION, class COMPARATOR_T>
	constexpr indexHeap Make_IndexHeap(COMPARATOR_T&& p_comparator_m) {
		return indexHeap(std::forward<COMPARATOR_T>(p_comparator_m));
	}

}

#undef indexHeap

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // JK_INDEX_HEAP
