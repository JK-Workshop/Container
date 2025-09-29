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

      constexpr auto Unite(const SIZE_T p_Target0_i, const SIZE_T p_Target1_i) noexcept -> void;

      JK_NODISCARD constexpr auto Find(const SIZE_T p_Target_i) noexcept -> const SIZE_T;

      JK_NODISCARD constexpr auto IsSame(const SIZE_T p_Target0_i, const SIZE_T p_Target1_i) noexcept -> const bool { return this->Find(p_Target0_i) == this->Find(p_Target1_i); }

    private:
      TUPLE_LIST_T tuple_l = TUPLE_LIST_T{};
      STACK_T stack = STACK_T();
      SIZE_T cnt = SIZE_T(0); // Stack counter
   };

   TEMPLATE constexpr auto CLASS_NAME::Unite(const SIZE_T p_Target0_i, const SIZE_T p_Target1_i) noexcept -> void
   {
      const auto i = this->Find(p_Target0_i);
      const auto j = this->Find(p_Target1_i);
      if (i == j) return;
      if (this->tuple_l[i].Tree_s < this->tuple_l[j].Tree_s) {
         this->tuple_l[i].Parent_i = j;
         this->tuple_l[j].Tree_s += this->tuple_l[i].Tree_s;
      } else {
         this->tuple_l[j].Parent_i = i;
         this->tuple_l[i].Tree_s += this->tuple_l[j].Tree_s;
      }
   }

   TEMPLATE constexpr auto CLASS_NAME::Find(const SIZE_T p_Target_i) noexcept -> const SIZE_T
   {
      auto i = this->tuple_l[p_Target_i].Parent_i;
      if (i == -1) return p_Target_i;
      while (true) {
         const auto j = this->tuple_l[i].Parent_i;
         if (j == -1) {
            while (this->cnt != 0)
               this->tuple_l[this->stack[--this->cnt]].Parent_i = i;
            return i;
         }
         this->stack[this->cnt++] = i;
         i = j;
      }
   }

#undef TEMPLATE
#undef CLASS_NAME

} // namespace JK

#endif // JK_UNION_FIND_SET_H
