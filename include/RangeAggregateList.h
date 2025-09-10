// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_RANGE_AGGREGATE_LIST_H)
#define JK_RANGE_AGGREGATE_LIST_H

#include "CompileTime.h"
#include <span>
#include <initializer_list>

#if defined(_DEBUG)
#include <print>
#endif // _DEBUG

namespace JK {

   enum class QueryAndUpdate_e : uint32_t {
      SINGLE_QUERY_RANGE_UPDATE,
      RANGE_QUERY_SINGLE_UPDATE,
      RANGE_QUERY_RANGE_UPDATE
   };

   template <class DATA_T, SIZE_T LIST_S, class AGGREGATE_T, DATA_T IDENTITY_V, QueryAndUpdate_e QUERY_AND_UPDATE_E>
   class RangeAggregateList {};

} // namespace JK

#endif // JK_RANGE_AGGREGATE_LIST_H
