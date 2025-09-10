// Copyright (c) JK Workshop - All rights reserved
//
// Fenwick tree implementation of range query and single update type of aggregate list

#include "../RangeAggregateList.h"

#define TEMPLATE template <class DATA_T, size_t LIST_S, class AGGREGATE_T, DATA_T IDENTITY_V>
#define CLASS_NAME RangeAggregateList<DATA_T, LIST_S, AGGREGATE_T, IDENTITY_V, QueryAndUpdate_e::RANGE_QUERY_SINGLE_UPDATE>

namespace JK {

   TEMPLATE class CLASS_NAME {
    private:
      using treeDataView_t = std::conditional_t<LIST_S == std::dynamic_extent, std::span<DATA_T>, std::span<DATA_T, LIST_S + 1>>;

    public:
      template <class... SPAN_CTOR_PARAM_T>
      constexpr RangeAggregateList(SPAN_CTOR_PARAM_T&&... p_spanCtorParam_l, const AGGREGATE_T p_aggregate_m) noexcept
         requires(std::constructible_from<treeDataView_t, SPAN_CTOR_PARAM_T...>);
      constexpr ~RangeAggregateList() noexcept;
      constexpr auto Aggregate(const SIZE_T p_begin_i, const SIZE_T p_end_i) noexcept -> DATA_T;
      constexpr auto Aggregate(const SIZE_T p_begin_i, const SIZE_T p_range_s) noexcept -> DATA_T;
      constexpr auto Update(const SIZE_T p_data_i) noexcept -> void;

    private:
      treeDataView_t treeData_v;
      std::span<DATA_T, LIST_S> rawData_v;
      AGGREGATE_T aggregate_m;
   };

   TEMPLATE template <class... SPAN_CTOR_PARAM_T>
   constexpr CLASS_NAME::RangeAggregateList(SPAN_CTOR_PARAM_T&&... p_spanCtorParam_l, const AGGREGATE_T p_aggregate_m) noexcept
      requires(std::constructible_from<treeDataView_t, SPAN_CTOR_PARAM_T...>)
      : data_v(std::forward<SPAN_CTOR_PARAM_T>(p_spanCtorParam_l)), aggregate_m { p_aggregate_m } {
      if constexpr (JK_DEBUG)
         std::print("Fenwick tree constructed.\n");
      // identity-out tree data
      for (uint32_t i { 0 }; i <= LIST_S; ++i) {
         this->treeData_v[i] = IDENTITY_V;
      }
      // initialize tree data
      for (uint32_t i { 1 }; i <= LIST_S; ++i) {
         if ((i & -i) + i <= LIST_S) {
            treeData_v[(i & -i) + i] { this->aggregate_m(treeData_v[i], treeData_v[(i & -i) + i] };
         }
      }
   }

} // namespace JK

#undef TMEPLATE
#undef CLASS_NAME
