// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_INDEX_HEAP)
#define JK_INDEX_HEAP

#include "CompileTime.h"

#include <array>
#include <span>
#include <memory>

namespace JK {

   enum class IndexHeapImpl_e : uint32_t {
      COSTUMED = 0,
      BINARY = 1,
      FIBONACCI = 2
   };

   template <class SIZE_T, const SIZE_T HEAP_S, class COMPARATOR_T, IndexHeapImpl_e IMPL_E>
   class IndexHeap {};
} // namespace JK

#include "IndexHeap/BinaryHeap.h"
#include "IndexHeap/FibonacciHeap.h"

#endif // JK_INDEX_HEAP
