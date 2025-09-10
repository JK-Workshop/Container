// Copyright (c) JK Workshop - All rights reserved
//
// Fixed sized list

#if !defined(JK_ARRAY_LIST_H)
#define JK_ARRAY_LIST_H

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

#define TEMPLATE template <class DATA_T, UintFast_tc auto LIST_S, class ITERATOR_T>
#define CLASS_NAME List<DATA_T, LIST_S, ITERATOR_T>

namespace JK {

   template <class DATA_T, UintFast_tc auto LIST_S, class ITERATOR_T = LinearIterator<DATA_T>>
   class List {
    public: // Out attributes
      using Data_t = DATA_T;
      using Size_t = decltype(LIST_S);
      using Iterator_t = ITERATOR_T;

    public:
      constexpr List() noexcept : data_v(), data_c(0) {}
      constexpr ~List() noexcept {}

      JK_NODISCARD constexpr Size_t Count() const noexcept { return this->data_c; }

      JK_NODISCARD constexpr Size_t Size() const noexcept { return LIST_S; }

      JK_NODISCARD constexpr bool IsEmpty() const noexcept { return this->Count() == 0; }

      JK_NODISCARD constexpr bool IsFull() const noexcept { return this->Count() == this->Size(); }

      template <class... CONSTRUCTOR_PARAMETERS_T>
      constexpr void PushBack(CONSTRUCTOR_PARAMETERS_T&&... p_) noexcept;

      template <bool DRY_POP = false>
      constexpr std::conditional_t<DRY_POP, void, DATA_T> PopBack() noexcept;

      constexpr DATA_T& operator[](const Size_t p_data_i) noexcept;
      constexpr const DATA_T& operator[](const Size_t p_data_i) const noexcept;

      constexpr void Flush() noexcept { this->data_c = 0; }

      JK_NODISCARD constexpr ITERATOR_T begin() noexcept { return static_cast<ITERATOR_T>(&(*this)[0]); }

      JK_NODISCARD constexpr ITERATOR_T end() noexcept { return static_cast<ITERATOR_T>(&(*this)[this->Count()]); }

    private:
      uint8_t data_v[LIST_S * sizeof(DATA_T)];
      Size_t data_c;
   };

   TEMPLATE template <class... CONSTRUCTOR_PARAMETERS_T>
   constexpr void CLASS_NAME::PushBack(CONSTRUCTOR_PARAMETERS_T&&... p_) noexcept {
      // DEBUG CHECK: emplace into a full list
      assert(!this->IsFull());
      // Construct element at the back of the list
      std::construct_at(&(*this)[this->data_c++], std::forward<CONSTRUCTOR_PARAMETERS_T>(p_)...);
   }

   TEMPLATE template <bool DRY_POP>
   JK_NODISCARD constexpr std::conditional_t<DRY_POP, void, DATA_T> CLASS_NAME::PopBack() noexcept {
      // DEBUG CHECK: pop from an empty list
      assert(!this->IsEmpty());
      if constexpr (DRY_POP) { // does not return popped value
         --this->data_c;
         if constexpr (std::is_class_v<DATA_T>)
            reinterpret_cast<DATA_T&>(this->data_v[this->data_c * sizeof(DATA_T)]).~DATA_T();
      } else { // return popped value
         if constexpr (std::is_move_constructible_v<DATA_T>) {
            DATA_T back_v = reinterpret_cast<DATA_T&&>(this->data_v[--this->data_c * sizeof(DATA_T)]);
            reinterpret_cast<DATA_T&>(this->data_v[this->data_c * sizeof(DATA_T)]).~DATA_T();
            return back_v;
         } else if constexpr (std::is_copy_constructible_v<DATA_T> || !std::is_class_v<DATA_T>) {
            DATA_T back_v = reinterpret_cast<DATA_T&>(this->data_v[--this->data_c * sizeof(DATA_T)]);
            if constexpr (std::is_class_v<DATA_T>)
               reinterpret_cast<DATA_T&>(this->data_v[this->data_c * sizeof(DATA_T)]).~DATA_T();
            return back_v;
         } else // the object is neither copy nor move constructible
            assert(false);
      }
   }

   TEMPLATE constexpr DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) noexcept {
      // DEBUG CHECK: index out of range
      assert(p_data_i < this->Count());
      // Accessing the element
      return reinterpret_cast<DATA_T&>(this->data_v[p_data_i * sizeof(DATA_T)]);
   }

   TEMPLATE constexpr const DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) const noexcept {
      // DEBUG CHECK: index out of range
      assert(p_data_i < this->Count());
      // Accessing the element
      return reinterpret_cast<const DATA_T&>(this->data_v[p_data_i * sizeof(DATA_T)]);
   }

} // namespace JK

#undef CLASS_NAME
#undef TEMPLATE

#include "List/DynamicList.h" // Dynamic sized Pool

#endif // JK_ARRAY_LIST
