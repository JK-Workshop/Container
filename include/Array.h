// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdlib.h>
#include <string.h>

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

namespace JK {

	template<class DATA_T, uint32_t ARRAY_S = 0, class ITERATOR_T = LinearIterator<DATA_T>>
	class Array {
		static_assert(ARRAY_S >= 0, "Error: array size shouldn't be negative.");
	private:
		uint32_t array_s;
		typename std::conditional_t<ARRAY_S == 0, DATA_T*, DATA_T[ARRAY_S]> data_v;
	public:
		/// <summary>
		/// Initialize an empty array with compile time size
		/// </summary>
		constexpr Array() noexcept(!JK_DEBUG) requires(ARRAY_S != 0)
			: data_v() {
		}
		/// <summary>
		/// Initialize an empty array with runtime size
		/// </summary>
		constexpr Array(uint32_t p_array_s) noexcept(!JK_DEBUG) requires(ARRAY_S == 0)
			: array_s(p_array_s), data_v((DATA_T*)malloc(p_array_s * sizeof(DATA_T))) {
		}
		/// <summary>
		/// Destroy an array
		/// </summary>
		constexpr ~Array() noexcept(!JK_DEBUG) {
			if constexpr (ARRAY_S == 0) {
				free(this->data_v);
			}
		}
		/// <summary>
		/// Query the number of elements in the array
		/// </summary>
		/// <returns> Number of elements in the array </returns>
		[[nodiscard("Unused array size")]]
		constexpr uint32_t Size() const noexcept(!JK_DEBUG) {
			if constexpr (ARRAY_S == 0)
				return this->array_s;
			else  return ARRAY_S;
		}
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]]
		constexpr DATA_T& operator[](uint32_t p_data_i) noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]]
		constexpr DATA_T& operator[](uint32_t p_data_i) const noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Reset this array with the values of other array (ct <- ct and rt <- rt)
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(const Array& other) const noexcept(!JK_DEBUG) {
			memcpy(this->data_v, other.data_v, this->Size() * sizeof(DATA_T));
		}
		/// <summary>
		/// Reset this array with the values of other array (ct <- rt)
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(const Array<DATA_T, 0, ITERATOR_T>& other) const noexcept(!JK_DEBUG) requires(ARRAY_S != 0) {
			if (this->Size() < other.Size())
				memcpy(this->data_v, other.data_v, this->Size() * sizeof(DATA_T));
			else   memcpy(this->data_v, other.data_v, other.Size() * sizeof(DATA_T));
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