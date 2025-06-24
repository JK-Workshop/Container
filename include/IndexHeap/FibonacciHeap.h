// Copyright (c) JK Workshop - All rights reserved

#include "IndexHeap.h"

namespace JK {

#	define IHeap IndexHeap<HEAP_S, COMPARE_T, IHeapImpl::FIBONACCI_HEAP>

	template<uint32_t HEAP_S, class COMPARE_T>
	class IHeap {
	public:
	private:
	};

#	undef IHeap

}