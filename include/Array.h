// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_ARRAY_H)
#define JK_ARRAY_H

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

#include <stdlib.h>
#include <string.h>

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

namespace JK {

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T = LinearIterator<DATA_T>>
	class Array {
		using Size_t = decltype(ARRAY_S);
	public:
		/// <summary>
		/// Initialize an empty array with compile time size
		/// </summary>
		constexpr Array() noexcept;
		/// <summary>
		/// Destroy an array
		/// </summary>
		constexpr ~Array() noexcept;
		/// <summary>
		/// Query the number of elements in the array
		/// </summary>
		/// <returns> Number of elements in the array </returns>
		constexpr Size_t Size() const noexcept;
		/// <summary>
		/// Pointer to the first element in the array
		/// </summary>
		/// <returns> pointer to the first element of array data </returns>
		constexpr DATA_T* Data() noexcept;
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](Size_t p_data_i) noexcept;
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](Size_t p_data_i) const noexcept;

		constexpr ITERATOR_T begin() noexcept;

		constexpr ITERATOR_T end() noexcept;
	private:
		DATA_T data_v[ARRAY_S];
	};

	// -------------------------------------------- Definition -------------------------------------------- //

#define array Array<DATA_T, ARRAY_S, ITERATOR_T>

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	constexpr array::Array() noexcept
		: data_v() {
	}

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	constexpr array::~Array() noexcept {}

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array size")]]
	constexpr typename array::Size_t array::Size() const noexcept { return ARRAY_S; }

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array data")]]
	constexpr DATA_T* array::Data() noexcept { return this->data_v; }

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array element")]]
	constexpr DATA_T& array::operator[](array::Size_t p_data_i) noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  JK_RT_BREAK("Index out of range")
		return this->data_v[p_data_i];
	}

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array element")]]
	constexpr DATA_T& array::operator[](array::Size_t p_data_i) const noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  JK_RT_BREAK("Index out of range")
		return this->data_v[p_data_i];
	}

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unsed array begin()")]]
	constexpr ITERATOR_T array::begin() noexcept { return ITERATOR_T(this->data_v); }

	template<JK::Fundmtal_t DATA_T, JK::UintFast_t auto ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array end()")]]
	constexpr ITERATOR_T array::end() noexcept { return ITERATOR_T(this->data_v + this->Size()); }

#undef array

}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // JK_ARRAY_H
