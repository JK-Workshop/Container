// Copyright (c) JK Workshop - All rights reserved
//
// Binary heap implementation of index heap

#include "../IndexHeap.h"

#define TEMPLATE template <class SIZE_T, const SIZE_T HEAP_S, class COMPARATOR_T>
#define CLASS_NAME IndexHeap<SIZE_T, HEAP_S, COMPARATOR_T, IndexHeapImpl_e::BINARY>

namespace JK {

   TEMPLATE class CLASS_NAME {
    private:
      using DataView_t = std::conditional_t<HEAP_S == std::dynamic_extent, std::span<SIZE_T>, std::span<SIZE_T, HEAP_S + 1>>;
      using HashList_t = std::conditional_t<HEAP_S == std::dynamic_extent, std::unique_ptr<SIZE_T[]>, std::array<SIZE_T, HEAP_S>>;

    public:
      IndexHeap() = delete;
      constexpr IndexHeap(const SIZE_T* p_data_l, const COMPARATOR_T& p_comparator) noexcept
         requires(HEAP_S != std::dynamic_extent);
      constexpr IndexHeap(const SIZE_T* p_data_l, const SIZE_T p_heap_s, const COMPARATOR_T& p_comparator) noexcept
         requires(HEAP_S == std::dynamic_extent);

      constexpr ~IndexHeap() noexcept {};

      JK_NODISCARD constexpr auto Count() const noexcept -> SIZE_T { return this->data_c; }

      JK_NODISCARD constexpr auto Size() const noexcept -> SIZE_T { return this->data_l.size() - 1; }

      JK_NODISCARD constexpr auto IsEmpty() const noexcept -> bool { return this->Count() == 0; }

      JK_NODISCARD constexpr auto IsFull() const noexcept -> bool { return this->Count() == this->Size(); }

      JK_NODISCARD constexpr auto Top() const noexcept -> SIZE_T;

      constexpr auto Push(const SIZE_T p_Target_v) noexcept -> void;

      constexpr auto Pop() noexcept -> SIZE_T;

      template <class DATA_T>
      constexpr auto Update(const DATA_T* p_Data_l, const SIZE_T p_Target_v, const DATA_T p_NewData_v) noexcept -> void;

    private:
      SIZE_T data_c = SIZE_T(0);
      DataView_t data_l;
      HashList_t hash_l = HashList_t();
      COMPARATOR_T comparator;

      constexpr auto shiftUp(SIZE_T p_Target_i) noexcept -> void;

      constexpr auto shiftDown(SIZE_T p_Target_i) noexcept -> void;
   };

   // -------------------------------------------- Definition -------------------------------------------- //

   TEMPLATE constexpr CLASS_NAME::IndexHeap(const SIZE_T* p_Data_l, const COMPARATOR_T& p_Comparator) noexcept
      requires(HEAP_S != std::dynamic_extent)
      : data_l(const_cast<SIZE_T*>(p_Data_l - 1), HEAP_S + 1),
        comparator(p_Comparator)
   {
      // Zero out hash list for future debug use
      if constexpr (JK_DEBUG)
         std::memset(this->hash_l, 0, HEAP_S * sizeof(SIZE_T));
   }

   TEMPLATE constexpr CLASS_NAME::IndexHeap(const SIZE_T* p_Data_t, const SIZE_T p_Heap_s, const COMPARATOR_T& p_Comparator) noexcept
      requires(HEAP_S == std::dynamic_extent)
      : data_l(const_cast<SIZE_T*>(p_Data_l - 1), p_Heap_s + 1),
        hash_l(std::make_unique<SIZE_T[]>(p_Heap_s)),
        comparator(p_Comparator)
   {
      // Zero out hash list for future debug use
      if constexpr (JK_DEBUG)
         std::memset(this->hash_l, 0, p_Heap_s * sizeof(SIZE_T));
   }

   TEMPLATE constexpr auto CLASS_NAME::Top() const noexcept -> SIZE_T
   {
      JK_VERIFY(this->IsEmpty() == false);
      return this->data_l[1];
   }

   TEMPLATE constexpr auto CLASS_NAME::Push(const SIZE_T p_Target_v) noexcept -> void
   {
      JK_VERIFY(this->IsFull() == false);
      ++this->data_c;
      this->data_l[this->data_c] = p_Target_v;
      this->shiftUp(this->data_c);
   }

   TEMPLATE constexpr auto CLASS_NAME::Pop() noexcept -> SIZE_T
   {
      // Zero the hash value of top for future debug use
      if constexpr (JK_DEBUG)
         this->hash_l[this->Top()] = 0;
      SIZE_T l_Popped_v = this->Top();
      this->data_l[1] = this->data_l[this->data_c];
      --this->data_c;
      this->shiftDown(1);
      return l_Popped_v;
   }

   TEMPLATE template <class DATA_T>
   constexpr auto CLASS_NAME::Update(const DATA_T* p_Data_l, const SIZE_T p_Target_v, const DATA_T p_NewData_v) noexcept -> void
   {
      JK_VERIFY(this->comparator(p_NewData_v, p_Data_l[p_Target_v]));
      // Check for p_target_v is in the heap
      JK_VERIFY(this->hash_l[p_Target_v] != 0);
      this->shiftUp(this->hash_l[p_Target_v]);
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftUp(SIZE_T p_Target_i) noexcept -> void
   {
      SIZE_T l_This_v = this->data_l[p_Target_i];
      SIZE_T l_Up_i = p_Target_i >> 1; // parent index of p_target_i
      while (l_Up_i != 0) {            // as long as not reaching the top
         if (this->comparator(l_This_v, this->data_l[l_Up_i])) {
            this->data_l[p_Target_i] = this->data_l[l_Up_i]; // bubble down up_i
            this->hash_l[this->data_l[p_Target_i]] = p_Target_i;
            p_Target_i = l_Up_i;
            l_Up_i >>= 1;
         } else
            break;
      }
      this->data_l[p_Target_i] = l_This_v;
      this->hash_l[l_This_v] = p_Target_i;
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftDown(SIZE_T p_Target_i) noexcept -> void
   {
      SIZE_T l_This_v = this->data_l[p_Target_i];
      SIZE_T l_Down_i = p_Target_i << 1;                                                               // "smaller" child of p_target_i between the two
      SIZE_T l_Last_i = this->data_c >> 1;                                                             // last non-leaf node
      while (p_Target_i <= l_Last_i) {                                                                 // as long as not reaching the bottom
         this->comparator(this->data_l[l_Down_i + 1], this->data_l[l_Down_i]) ? ++l_Down_i : l_Down_i; // the "smaller" one
         if (this->comparator(this->data_l[l_Down_i], l_This_v)) {                                     // even the "smaller" one is "larger"
            this->data_l[p_Target_i] = this->data_l[l_Down_i];                                         // bubble up down_i
            this->hash_l[this->data_l[p_Target_i]] = p_Target_i;
            p_Target_i = l_Down_i;
            l_Down_i <<= 1;
         } else
            break;
      }
      this->data_l[p_Target_i] = l_This_v;
      this->hash_l[l_This_v] = p_Target_i;
   }

} // namespace JK

#undef CLASS_NAME
#undef TMEPLATE
