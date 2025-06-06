// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_LINEAR_ITERATOR_H)
#define JK_LINEAR_ITERATOR_H

#include "CompileTime.h"

namespace JK {

	/// <summary>
	/// Iterator for linear structure such as array, list, linked list etc.
	/// </summary>
	/// <typeparam name="DATA_T"> type of element in linear data structure </typeparam>
	template<class DATA_T>
	class LinearIterator {
	private:
		DATA_T* pointer;
	public:
		constexpr LinearIterator(DATA_T* p_pointer) noexcept
			: pointer(p_pointer) {
		}
		constexpr LinearIterator(const LinearIterator& p_other) noexcept
			: pointer(p_other.pointer) {
		}
		LinearIterator& operator=(const LinearIterator& p_other) {
			p_other.pointer = this->pointer;
		}
		// ------------- Delete unecessary functions ------------- //
		LinearIterator() = delete;
		LinearIterator(LinearIterator&&) = delete;
		LinearIterator& operator=(LinearIterator&&) = delete;

		constexpr DATA_T& operator*() const noexcept {
			return *this->pointer;
		}
		constexpr DATA_T* operator->() const noexcept {
			return this->pointer;
		}
		constexpr DATA_T& operator[](uint32_t p_data_i) const noexcept {
			return pointer[p_data_i];
		}
		constexpr LinearIterator& operator++() noexcept {
			++this->pointer;
			return *this;
		}
		constexpr LinearIterator& operator--() noexcept {
			--this->pointer;
			return *this;
		}
		[[nodiscard("Unused incremented value, use prefix operator++ instead")]]
		constexpr LinearIterator operator++(int) noexcept {
			LinearIterator tmpIterator = *this;
			++*this;
			return tmpIterator;
		}
		[[nodiscard("Unused decremented value, use prefix operator-- instead")]]
		constexpr LinearIterator operator--(int) noexcept {
			LinearIterator tmpIterator = *this;
			--*this;
			return tmpIterator;
		}
		constexpr bool operator==(const LinearIterator& p_other) const noexcept {
			return this->pointer == p_other.pointer;
		}
		constexpr bool operator!=(const LinearIterator& p_other) const noexcept {
			return !(*this == p_other);
		}
	};

}

#endif // JK_LINEAR_ITERATOR_H