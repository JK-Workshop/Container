// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_HEAP_H)
#define JK_HEAP_H

#include "CompileTime.h"

#include <array>
#include <memory>
#include <span>

namespace JK {

   enum class HeapImpl_e : uint32_t {
      COSTUMED = 0,
      BINARY = 1,
      FIBONACCI = 2
   };

   template <std::unsigned_integral auto HEAP_S, class COMPARATOR_T, HeapImpl_e IMPL_E>
   class IdxHeap {};

   template <class DATA_T, std::unsigned_integral auto HEAP_S, class COMPARATOR_T, HeapImpl_e IMPL_E>
   class PtrHeap {};

} // namespace JK

#include "Heap/Binary.h"
#include "Heap/Fibonacci.h"

#endif // JK_HEAP_H
