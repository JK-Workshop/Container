// Copyright (c) JK Workshop - All rights reserved
//
// Binary heap implementation of index heap

#include "../Heap.h"

namespace JK {

#define TEMPLATE template <std::unsigned_integral auto HEAP_S, class COMPARATOR_T>
#define CLASS_NAME IdxHeap<HEAP_S, COMPARATOR_T, HeapImpl_e::BINARY>

   TEMPLATE class CLASS_NAME {
    private:
      using SIZE_T = decltype(HEAP_S);
      using LIST_T = std::span<SIZE_T, HEAP_S == -1 ? -1 : HEAP_S + 1>;
      using HASH_T = std::conditional_t<HEAP_S == -1, std::unique_ptr<SIZE_T[]>, std::array<SIZE_T, HEAP_S>>;

    public:
      using SIZE_TYPE = SIZE_T;
      using DATA_TYPE = LIST_T;
      using COMPARATOR_TYPE = COMPARATOR_T;
      static constexpr auto IMPLEMENTATION = HeapImpl_e::BINARY;

    public:
      IdxHeap() = delete;

      constexpr IdxHeap(SIZE_T* p_DataList_p, const COMPARATOR_T& p_Comparator) noexcept
         requires(HEAP_S != -1);

      constexpr IdxHeap(SIZE_T* p_DataList_p, SIZE_T p_Heap_p, const COMPARATOR_T& p_Comparator) noexcept
         requires(HEAP_S == -1);

      constexpr ~IdxHeap() noexcept {};

      JK_NODISCARD constexpr auto Count() const noexcept -> SIZE_T { return this->data_c; }

      JK_NODISCARD constexpr auto Size() const noexcept -> SIZE_T { return this->data_l.size() - 1; }

      JK_NODISCARD constexpr auto IsEmpty() const noexcept -> bool { return this->Count() == 0; }

      JK_NODISCARD constexpr auto IsFull() const noexcept -> bool { return this->Count() == this->Size(); }

      JK_NODISCARD constexpr auto Top() const noexcept -> SIZE_T;

      constexpr auto Push(SIZE_T p_Target_v) noexcept -> void;

      constexpr auto Pop() noexcept -> void;

      template <class DATA_T, class UPDATER_T>
      constexpr auto Update(DATA_T* p_DataList_p, SIZE_T p_Target_v, UPDATER_T&& p_Updater) noexcept -> void;

    private:
      SIZE_T data_c = SIZE_T(0);
      LIST_T data_l;
      HASH_T hash_l;
      COMPARATOR_T comparator;

      constexpr auto shiftUp(SIZE_T ti) noexcept -> void;

      constexpr auto shiftDown(SIZE_T ti) noexcept -> void;
   };

   // -------------------------------------------- Definition -------------------------------------------- //

   TEMPLATE constexpr CLASS_NAME::IdxHeap(SIZE_T* p_DataList_p, const COMPARATOR_T& p_Comparator) noexcept
      requires(HEAP_S != -1)
      : data_l(p_DataList_p - 1, static_cast<size_t>(HEAP_S + 1)),
        comparator(p_Comparator)
   {
      // Zero out hash list for future debug use
      if constexpr (JK_DEBUG)
         std::memset(this->hash_l, 0, HEAP_S * sizeof(SIZE_T));
   }

   TEMPLATE constexpr CLASS_NAME::IdxHeap(SIZE_T* p_DataList_p, SIZE_T p_Heap_s, const COMPARATOR_T& p_Comparator) noexcept
      requires(HEAP_S == -1)
      : data_l(p_DataList_p - 1, static_cast<size_t>(p_Heap_s + 1)),
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

   TEMPLATE constexpr auto CLASS_NAME::Push(SIZE_T p_Target_v) noexcept -> void
   {
      JK_VERIFY(this->IsFull() == false);
      ++this->data_c;
      this->data_l[this->data_c] = p_Target_v;
      this->shiftUp(this->data_c);
   }

   TEMPLATE constexpr auto CLASS_NAME::Pop() noexcept -> void
   {
      // Zero the hash value of top for future debug use
      if constexpr (JK_DEBUG)
         this->hash_l[this->Top()] = 0;
      this->data_l[1] = this->data_l[this->data_c];
      --this->data_c;
      this->shiftDown(1);
   }

   TEMPLATE template <class DATA_T, class UPDATER_T>
   constexpr auto CLASS_NAME::Update(DATA_T* p_DataList_p, SIZE_T p_Target_v, UPDATER_T&& p_Updater) noexcept -> void
   {
      p_Updater();
      //JK_VERIFY(this->comparator(l_NewData_v, p_DataList_p[p_Target_v]));
      // Check for p_target_v is in the heap
      JK_VERIFY(this->hash_l[p_Target_v] != 0);
      this->shiftUp(this->hash_l[p_Target_v]);
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftUp(SIZE_T ti) noexcept -> void
   {
      const auto i = this->data_l[ti];
      auto ui = ti >> 1; // parent index of p_target_i
      while (ui != 0) {  // as long as not reaching the top
         if (this->comparator(i, this->data_l[ui])) {
            this->data_l[ti] = this->data_l[ui]; // bubble down up_i
            this->hash_l[this->data_l[ti]] = ti;
            ti = ui;
            ui >>= 1;
         } else
            break;
      }
      this->data_l[ti] = i;
      this->hash_l[i] = ti;
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftDown(SIZE_T ti) noexcept -> void
   {
      const auto i = this->data_l[ti];
      auto di = ti << 1;                                                       // "smaller" child of p_target_i between the two
      const auto li = this->data_c >> 1;                                       // last non-leaf node
      while (ti <= li) {                                                       // as long as not reaching the bottom
         this->comparator(this->data_l[di + 1], this->data_l[di]) ? ++di : di; // the "smaller" one
         if (this->comparator(this->data_l[di], i)) {                          // even the "smaller" one is "larger"
            this->data_l[ti] = this->data_l[di];                               // bubble up down_i
            this->hash_l[this->data_l[ti]] = ti;
            ti = di;
            di <<= 1;
         } else
            break;
      }
      this->data_l[ti] = i;
      this->hash_l[i] = ti;
   }

#undef CLASS_NAME
#undef TMEPLATE

   // ============================================================================================================================= //

#define TEMPLATE template <class DATA_T, std::unsigned_integral auto HEAP_S, class COMPARATOR_T>
#define CLASS_NAME PtrHeap<DATA_T, HEAP_S, COMPARATOR_T, HeapImpl_e::BINARY>

   TEMPLATE class CLASS_NAME {
    private:
      using SIZE_T = decltype(HEAP_S);
      using LIST_T = std::span<DATA_T*, HEAP_S == -1 ? -1 : HEAP_S + 1>;

    public:
      using SIZE_TYPE = SIZE_T;
      using DATA_TYPE = DATA_T;
      static constexpr auto IMPLEMENTATION = HeapImpl_e::BINARY;

    public:
      PtrHeap() = delete;

      constexpr PtrHeap(DATA_T** p_DataList_p, const COMPARATOR_T& p_Comparator) noexcept
         requires(HEAP_S != -1)
         : data_l(p_DataList_p - 1, HEAP_S + 1),
           comparator(p_Comparator) {};

      constexpr PtrHeap(DATA_T** p_DataList_p, SIZE_T p_Heap_s, const COMPARATOR_T& p_Comparator) noexcept
         requires(HEAP_S == -1)
         : data_l(p_DataList_p - 1, p_Heap_s + 1),
           comparator(p_Comparator) {};

      JK_NODISCARD constexpr auto Count() const noexcept -> SIZE_T { return this->data_c; }

      JK_NODISCARD constexpr auto Size() const noexcept -> SIZE_T { return this->data_l.size() - 1; }

      JK_NODISCARD constexpr auto IsEmpty() const noexcept -> bool { return this->Count() == 0; }

      JK_NODISCARD constexpr auto IsFull() const noexcept -> bool { return this->Count() == this->Size(); }

      JK_NODISCARD constexpr auto Top() const noexcept -> DATA_T* { return this->data_l[1]; }

      constexpr auto Push(DATA_T* p_Target_p) noexcept -> void;

      constexpr auto Pop() noexcept -> void;

    private:
      SIZE_T data_c = SIZE_T(0);
      LIST_T data_l = LIST_T();
      COMPARATOR_T comparator;

      constexpr auto shiftUp(SIZE_T ti) noexcept -> void;

      constexpr auto shiftDown(SIZE_T ti) noexcept -> void;
   };

   // -------------------------------------------- Definition -------------------------------------------- //

   TEMPLATE constexpr auto CLASS_NAME::Push(DATA_T* p_Target_p) noexcept -> void
   {
      JK_VERIFY(this->IsFull() == false);
      ++this->data_c;
      this->data_l[this->data_c] = p_Target_p;
      this->shiftUp(this->data_c);
   }

   TEMPLATE constexpr auto CLASS_NAME::Pop() noexcept -> void
   {
      JK_VERIFY(this->IsEmpty() == false);
      this->data_l[1] = this->data_l[this->data_c];
      --this->data_c;
      this->shiftDown(1);
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftUp(SIZE_T ti) noexcept -> void
   {
      const auto p = this->data_l[ti];
      while (ti != 1) {
         const auto ui = ti >> 1;
         const auto up = this->data_l[ui];
         if (this->comparator(p, up)) {
            this->data_l[ti] = up;
         } else
            break;
         ti = ui;
      }
      this->data_l[ti] = p;
   }

   TEMPLATE constexpr auto CLASS_NAME::shiftDown(SIZE_T ti) noexcept -> void
   {
      const auto p = this->data_l[ti];
      const auto li = this->data_c >> 1; // Last non-leaf index
      auto di = ti << 1;
      while (ti <= li) {
         this->comparator(this->data_l[di + 1], this->data_l[di]) ? ++di : di;
         if (this->comparator(this->data_l[di], p)) {
            this->data_l[ti] = this->data_l[di];
            ti = di;
            di <<= 1;
         } else
            break;
      }
      this->data_l[ti] = p;
   }

#undef TEMPLATE
#undef CLASS_NAME

} // namespace JK
