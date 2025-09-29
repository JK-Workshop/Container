// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_UNION_FIND_SET_H)
#define JK_UNION_FIND_SET_H

#include "CompileTime.h"

#include <array>
#include <memory>

namespace JK {

#define TEMPLATE template <std::unsigned_integral auto SET_S>
#define CLASS_NAME IdxUnionFindSet<SET_S>

   TEMPLATE class IdxUnionFindSet {
    private:
      using SIZE_T = decltype(SET_S);
      struct tuple_t {
         SIZE_T Parent_i = SIZE_T(-1);
         SIZE_T Tree_s = SIZE_T(1);
      };
      using TUPLE_LIST_T = std::conditional_t<SET_S == -1, std::unique_ptr<tuple_t[]>, std::array<tuple_t, SET_S>>;
      using STACK_T = std::conditional_t<SET_S == -1, std::unique_ptr<SIZE_T[]>, std::array<SIZE_T, SET_S>>;

    public:
      using SIZE_TYPE = SIZE_T;
      static constexpr auto SET_SIZE = SIZE_T(SET_S);

    public:
      constexpr IdxUnionFindSet(const SIZE_T p_Set_s) noexcept
         requires(SET_S != std::dynamic_extent)
      {
      }

      constexpr IdxUnionFindSet(const SIZE_T p_Set_s) noexcept
         requires(SET_S == std::dynamic_extent)
         : tuple_l(std::make_unique<tuple_t[]>(p_Set_s)),
           stack(std::make_unique<SIZE_T[]>(p_Set_s))
      {
      }

      constexpr auto Unite(SIZE_T p_Target0_i, SIZE_T p_Target1_i) noexcept -> void;

      JK_NODISCARD constexpr auto Find(SIZE_T p_Target_i) noexcept -> SIZE_T;

    private:
      TUPLE_LIST_T tuple_l = TUPLE_LIST_T{};
      STACK_T stack = STACK_T();
      SIZE_T cnt = SIZE_T(0); // Stack counter
   };

   TEMPLATE constexpr auto CLASS_NAME::Unite(SIZE_T p_Target0_i, SIZE_T p_Target1_i) noexcept -> void
   {
      const auto i = this->Find(p_Target0_i);
      const auto j = this->Find(p_Target1_i);
      if (i == j) return;
      if (this->treeSize_l[i] < this->treeSize_l[j]) {
         this->parentIdx_l[i] = j;
         this->treeSize_l[j] += this->treeSize_l[i];
      } else {
         this->parentIdx_l[j] = i;
         this->treeSize_l[i] += this->treeSize_l[j];
      }
   }

   TEMPLATE constexpr auto CLASS_NAME::Find(SIZE_T p_Target_i) noexcept -> SIZE_T
   {
      auto i = this->tuple_l[p_Target_i].Parent_i;
      if (i == -1)  return p_Target_i;
      while (1) {
         const auto j = this->tuple_l[i].Parent_i;
         if (j == -1) {
            do this->tuple_l[this->stack[--this->cnt]].Parent_i = i;
            while (this->cnt);
            return i;
         }
         this->stack[cnt++] = i;
         i = j;
      }
   }

#undef TEMPLATE
#undef CLASS_NAME

#define TEMPLATE template <class DATA_T, std::unsigned_integral auto SET_S>
#define CLASS_NAME PtrUnionFindSet<DATA_T, SET_S>

   TEMPLATE class PtrUnionFindSet {
    private:
      using SIZE_T = decltype(SET_S);
      struct pair {
         DATA_T* Data_p;
         pair* Parent_p = pair * (nullptr);
         SIZE_T Tree_s = SIZE_T(1);
      };
      using PAIR_LIST_T = std::conditional_t<SET_S == -1, std::unique_ptr<pair[]>, std::array<pair, SET_S>>;
      using LIST_T = std::conditional_t<SET_S == -1, std::unique_ptr<SIZE_T[]>, std::array<SIZE_T, SET_S>>;

    public:
      using SIZE_TYPE = SIZE_T;
      static constexpr auto SET_SIZE = SET_S;

    public:
      constexpr PtrUnionFindSet() noexcept
         requires(SET_S != -1)
      {
      }

      constexpr PtrUnionFindSet(const SIZE_T p_Set_s) noexcept
         requires(SET_S == -1)
         : pair_l(std::make_unique<pair[]>(p_Set_s))
      {
      }

      constexpr auto Unite(const DATA_T* p_DataPtr0_v, const DATA_T* p_DataPtr1_v) noexcept -> void;

      constexpr auto Find(const DATA_T* p_DataPtr_v) noexcept -> DATA_T*;

      constexpr auto Same(const DATA_T* p_DataPtr0_v, const DATA_T* p_DataPtr1_v) noexcept -> bool { return this->Find(p_DataPtr0_v) == this->Find(p_DataPtr1_v); }

    private:
      PAIR_LIST_T pair_l;
   };

   TEMPLATE constexpr auto CLASS_NAME::Unite(const DATA_T* p_DataPtr0_v, const DATA_T* p_DataPtr1_v) noexcept -> void
   {
      const auto p = static_cast<pair*>(this->Find(p_DataPtr0_v));
      const auto q = static_cast<pair*>(this->Find(p_DataPtr1_v));
      if (p == q) return;
      if (p->Tree_s < q->Tree_s) {
         p->Parent_p = static_cast<DATA_T*>(q);
         q->Tree_s += p->Tree_s;
      } else {
         q->Parent_p = static_cast<DATA_T*>(p);
         p->Tree_s += q->Tree_s;
      }
   }

   TEMPLATE constexpr auto CLASS_NAME::Find(const DATA_T* p_DataPtr_v) noexcept -> DATA_T*
   {
      auto p = static_cast<pair*>(p_DataPtr_v)->Parent_p;
      while (p != nullptr) {
         auto gp = p->Parent_p;
         if (gp == nullptr)
            return p;
         p = gp;
      }
      return p_DataPtr_v;
   }

} // namespace JK

#endif // JK_UNION_FIND_SET_H
