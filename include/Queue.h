// Copyright (c) JK Workshop - All rights reserved

#include "CompileTime.h"
#include <span>

namespace JK {

   template <class DATA_T, std::unsigned_integral auto QUEUE_S>
   class Queue {
    private:
      using SIZE_T = decltype(QUEUE_S);

    public:
      constexpr Queue(const DATA_T* const p_Data_l) noexcept
         requires(std::QUEUE_S != std::dynamic_extent)
         : data_l(p_Data_l, QUEUE_S) {};

      constexpr Queue(const DATA_T* const p_Data_l, const SIZE_T p_Queue_s) noexcept
         requires(std::QUEUE_S == std::dynamic_extent)
         : data_l(p_Data_l, p_Queue_s) {};

      constexpr auto Size() noexcept -> SIZE_T { return this->data_l.size(); };

      constexpr auto IsEmpty() noexcept -> bool { return this->front_i == this->back_i;  };

      constexpr auto IsFull() noexcept -> bool { return this->back_i};

      constexpr auto Push(const DATA_T& p_Target_v) noexcept -> void;

      template<bool IS_DRY_POP>
      constexpr auto Pop() noexcept -> void;

    private:
      auto data_l = std::span<DATA_T, QUEUE_S>();
      auto front_i = SIZE_T(0);
      auto back_i = SIZE_T(0);
   };

} // namespace JK