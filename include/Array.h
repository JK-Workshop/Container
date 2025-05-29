// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <string.h>

#include "CompileTime.h"

namespace JK {

	template<class DATA_T>
	class ArrayIterator {
	private:
		DATA_T* tracker_ptr;
	public:
		constexpr ArrayIterator(DATA_T* p_tracker_ptr) noexcept(!JK_DEBUG)
			: tracker_ptr(p_tracker_ptr) {
		}
		constexpr ArrayIterator(ArrayIterator& other) noexcept(!JK_DEBUG)
			: tracker_ptr(other.tracker_ptr) {
		}
		constexpr ~ArrayIterator() noexcept(!JK_DEBUG) {
		}
		constexpr DATA_T& operator*() const noexcept(!JK_DEBUG) {
			return *this->tracker_ptr;
		}
		constexpr DATA_T* operator->() const noexcept(!JK_DEBUG) {
			return this->tracker_ptr;
		}
		constexpr  DATA_T& operator[](size_t p_data_i) const noexcept(!JK_DEBUG) {
			return tracker_ptr[p_data_i];
		}
		constexpr ArrayIterator& operator++() noexcept(!JK_DEBUG) {
			this->tracker_ptr++;
			return *this;
		}
		[[nodiscard("Unused incremented value, use prefix++ instead")]]
		constexpr ArrayIterator operator++(int) noexcept(!JK_DEBUG) {
			ArrayIterator tmpIterator = *this;
			this->tracker_ptr++;
			return tmpIterator;
		}
		constexpr ArrayIterator& operator--() noexcept(!JK_DEBUG) {
			this->tracker_ptr--;
			return *this;
		}
		[[nodiscard("Unused decremented value, use prefix-- instead")]]
		constexpr ArrayIterator operator--(int) noexcept(!JK_DEBUG) {
			ArrayIterator tmpIterator = *this;
			this->tracker_ptr--;
			return tmpIterator;
		}
		constexpr bool operator==(ArrayIterator& p_other) noexcept(!JK_DEBUG) {
			return this->tracker_ptr == p_other.tracker_ptr;
		}
		constexpr bool operator!=(ArrayIterator& p_other) noexcept(!JK_DEBUG) {
			return this->tracker_ptr != p_other.tracker_ptr;
		}
	};

	template<class DATA_T, size_t ARRAY_S, class ITERATOR_T = ArrayIterator<DATA_T>>
	class Array {
	private:
		DATA_T data_v[ARRAY_S];
	public:
		/// <summary>
		/// Initialize an empty array
		/// </summary>
		constexpr Array() noexcept(!JK_DEBUG)
			: data_v() {
		}
		/// <summary>
		/// 
		/// </summary>
		constexpr ~Array() noexcept(!JK_DEBUG) {
		}
		/// <summary>
		/// Query the number of elements in the array
		/// </summary>
		/// <returns> Number of elements in the array </returns>
		[[nodiscard("Unused array size")]]
		constexpr size_t Size() const noexcept(!JK_DEBUG) {
			return ARRAY_S;
		}
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]]
		constexpr DATA_T& operator[](size_t p_data_i) noexcept(!JK_DEBUG) {
			JK_VERIFY(p_data_i <= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]]
		constexpr DATA_T& operator[](size_t p_data_i) const noexcept(!JK_DEBUG) {
			JK_VERIFY(p_data_i <= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Reset current array with a copy of another array
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(Array& other) const noexcept(!JK_DEBUG) {
			memcpy(other.data_v, this->data_v, this->Size());
		}
		[[nodiscard("Unsed array begin()")]]
		constexpr ITERATOR_T begin() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v);
		}
		[[nodiscard("Unused array end()")]]
		constexpr ITERATOR_T end() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v + this->Size());
		}

	};
}