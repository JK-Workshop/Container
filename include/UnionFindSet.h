// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_UNION_FIND_SET_H)
#define JK_UNION_FIND_SET_H

#include "CompileTime.h"

#define TEMPLATE template <std::unsigned_integral auto SET_S>
#define CLASS_NAME UnionFindSet<SET_S>

namespace JK {

   template <std::unsigned_integral auto SET_S>
   class UnionFindSet {
    private:
      using SIZE_T = decltype(SET_S);

    public:
      using SIZE_TYPE = SIZE_T;
      static constexpr auto SET_SIZE = SIZE_T(SET_S);

    public:
      constexpr UnionFindSet(const SIZE_T p_Set_s) noexcept
         requires(SET_S != std::dynamic_extent);

      constexpr UnionFindSet(const SIZE_T p_Set_s) noexcept
         requires(SET_S == std::dynamic_extent);

      constexpr auto Unite(SIZE_T p_DataIdx0_v, SIZE_T p_DataIdx1_v) noexcept -> void;

      JK_NODISCARD constexpr auto Find(SIZE_T p_DataIdx_v) noexcept -> SIZE_T;

    private:
      LIST_T<SIZE_T, SET_S> parentIdx_l{};
      LIST_T<SIZE_T, SET_S> treeSize_l{};
   };

   TEMPLATE constexpr CLASS_NAME::UnionFindSet(const SIZE_T p_Set_s) noexcept
      requires(SET_S != std::dynamic_extent)
   {
      for (auto i = SIZE_T(0); i < SET_S; ++i)
         this->parentIdx_l[i] = i;
   }

   TEMPLATE constexpr CLASS_NAME::UnionFindSet(const SIZE_T p_Set_s) noexcept
      requires(SET_S == std::dynamic_extent)
      : parentIdx_l(std::make_unique<SIZE_T[]>(p_Set_s)),
        treeSize_l(std::make_unique<SIZE_T[]>(p_Set_s))
   {
      for (auto i = SIZE_T(0); i < p_Set_s; ++i)
         this->parentIdx_l[i] = i;
   }

   TEMPLATE constexpr auto CLASS_NAME::Unite(SIZE_T p_DataIdx0_v, SIZE_T p_DataIdx1_v) noexcept -> void
   {
      const auto p0 = this->Find(p_DataIdx0_v);
      const auto p1 = this->Find(p_DataIdx1_v);
      if (this->treeSize_l[p0] < this->treeSize_l[p1]) {
         this->parentIdx_l[p0] = p1;
         this->treeSize_l[p1] += this->treeSize_l[p0];
      } else {
         this->parentIdx_l[p1] = p0;
         this->treeSize_l[p0] += this->treeSize_l[p1];
      }
   }

   TEMPLATE constexpr auto CLASS_NAME::Find(SIZE_T p_DataIdx_v) noexcept -> SIZE_T
   {
      auto pp = &this->parentIdx_l[p_DataIdx_v];
      while (*pp != p_DataIdx_v) {
         auto gp = &this->parentIdx_l[*pp];
         if (*pp == *gp)
            return *pp;
         p_DataIdx_v = *pp;
         pp = gp;
      }
      return p_DataIdx_v;
   }

} // namespace JK

#undef TEMPLATE
#undef CLASS_NAME

#endif // JK_UNION_FIND_SET_H
