// Copyright (c) JK Workshop - All rights reserved
//
// Dynamic sized Pool

#include "../List.h"

#define TEMPLATE template <class DATA_T, class ITERATOR_T>
#define CLASS_NAME List<DATA_T, 0u, ITERATOR_T>

namespace JK {

   template <class DATA_T, class ITERATOR_T>
   class CLASS_NAME {
    public:
      using Data_t = DATA_T;
      using Size_t = SIZE_T;
      using Iterator_t = ITERATOR_T;

    public:
      constexpr List(const Size_t p_list_s) noexcept;
      constexpr ~List() noexcept;

      JK_NODISCARD constexpr Size_t Count() const noexcept { return this->data_c; }

      JK_NODISCARD constexpr Size_t Size() const noexcept { return this->list_s; }

      JK_NODISCARD constexpr bool IsEmpty() const noexcept { return this->Count() == 0; }

      JK_NODISCARD constexpr DATA_T* Data() const noexcept { return this->data_v; }

      template <class... CONSTRUCTOR_PARAMETERS_T>
      constexpr void PushBack(CONSTRUCTOR_PARAMETERS_T&&... p_) noexcept;

      template <bool DRY_POP = false>
      constexpr std::conditional_t<DRY_POP, void, DATA_T> PopBack() noexcept;

      constexpr DATA_T& operator[](const Size_t p_data_i) noexcept;
      constexpr const DATA_T& operator[](const Size_t p_data_i) const noexcept;

      template <bool RESET_SIZE = false>
      constexpr void Flush() noexcept;

      constexpr void Truncate(const Size_t p_newList_s) noexcept;

      JK_NODISCARD constexpr ITERATOR_T begin() noexcept { return static_cast<ITERATOR_T>(&this->data_v[0]); }

      JK_NODISCARD constexpr ITERATOR_T end() noexcept { return static_cast<ITERATOR_T>(&this->data_v[this->data_c]); }

    protected:
      DATA_T* data_v;
      Size_t data_c, list_s;

      constexpr void grow() noexcept;
   };

   TEMPLATE constexpr CLASS_NAME::List(const CLASS_NAME::Size_t p_list_s) noexcept : data_v(static_cast<DATA_T*>(malloc(p_list_s * sizeof(DATA_T)))), data_c(0), list_s(p_list_s) {
      // Error handling of failed heap allocation
      if (data_v == nullptr) [[unlikely]]
         JK_RT_BREAK("Heap allocation failed for array list data")
   }

   TEMPLATE constexpr CLASS_NAME::~List() noexcept {
      free(this->data_v);
      // DEBUG SET: zero out all members for subsequent debug checks
      if constexpr (JK_DEBUG) {
         this->data_v = nullptr;
         this->data_c = this->list_s = 0;
      }
   }

   TEMPLATE template <class... CONSTRUCTOR_PARAMETERS_T>
   constexpr void CLASS_NAME::PushBack(CONSTRUCTOR_PARAMETERS_T&&... p_) noexcept {
      // Grow the size if it hits the current limit
      if (this->Count() >= this->Size())
         this->grow();
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
            this->data_v[this->data_c].~DATA_T();
      } else { // return popped value
         if constexpr (std::is_move_constructible_v<DATA_T>) {
            DATA_T back_v = std::move(this->data_v[--this->data_c]);
            this->data_v[this->data_c].~DATA_T();
            return back_v;
         } else if constexpr (std::is_copy_constructible_v<DATA_T> || !std::is_class_v<DATA_T>) {
            DATA_T back_v = this->data_v[--this->data_c];
            if constexpr (std::is_class_v<DATA_T>)
               this->data_v[this->data_c].~DATA_T();
            return back_v;
         } else // the object is neither copy nor move constructible
            assert(false);
      }
   }

   TEMPLATE constexpr DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) noexcept {
      // DEBUG CHECK: index out of range
      assert(p_data_i < this->Count());
      // Accessing the element
      return this->data_v[p_data_i];
   }

   TEMPLATE constexpr const DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) const noexcept {
      // DEBUG CHECK: index out of range
      assert(p_data_i < this->Count());
      // Accessing the element
      return this->data_v[p_data_i];
   }

   TEMPLATE template <bool RESET_SIZE>
   constexpr void CLASS_NAME::Flush() noexcept {
      while (this->data_c)
         this->data_v[--this->data_c].~DATA_T();
      // Reset pool size to 1 if enabled
      if constexpr (RESET_SIZE)
         this->list_s = 1;
   }

   TEMPLATE constexpr void CLASS_NAME::Truncate(const Size_t p_newList_s) noexcept {
      // Check if p_newArrayList_s is less than current size
      assert(p_newList_s < this->list_s);
      // Desctruct extra elements
      while (this->data_c > p_newList_s)
          this->data_v[--this->data_c].~DATA_T();
      // Reallocation
      this->data_v = static_cast<DATA_T*>(realloc(this->data_v, p_newList_s * sizeof(DATA_T)));
      // Error handling of failed reallocatilon
      if (this->data_v == nullptr) [[unlikely]] {
         this->~List();
         JK_RT_BREAK("Heap reallocation failed for list data")
      }
   }

   TEMPLATE constexpr void CLASS_NAME::grow() noexcept {
      // Reallocation with growth factor 2
      this->list_s <<= 1;
      this->data_v = static_cast<DATA_T*>(realloc(this->data_v, this->list_s * sizeof(DATA_T)));
      // Error handling of failed reallocation
      if (this->data_v == nullptr) [[unlikely]] {
         JK_RT_BREAK("Heap reallocation failed for list data")
         this->~List();
      }
   }

} // namespace JK
