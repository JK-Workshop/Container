// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_ARRAY_H)
#define JK_ARRAY_H

#include <stdlib.h>
#include <string.h>

#include "CompileTime/UniversalCT.h"
#include "Iterator/LinearIterator.h"

namespace JK {

	enum class ArrayErr : uint32_t {
		ARRAY_SUCCESS = 0,
		ARRAY_INDEX_OUT_OF_RANGE = 1
	};

	template<class DATA_T, uint32_t ARRAY_S = 0, class ITERATOR_T = LinearIterator<DATA_T>>
	class Array {
	public:
		/// <summary>
		/// Initialize an empty array with compile time size
		/// </summary>
		constexpr Array() noexcept requires(ARRAY_S != 0);

		/// <summary>
		/// Initialize an empty array with runtime size
		/// </summary>
		constexpr Array(uint32_t p_array_s) noexcept requires(ARRAY_S == 0);

		/// <summary>
		/// Destroy an array
		/// </summary>
		constexpr ~Array() noexcept;

		/// <summary>
		/// Query the number of elements in the array
		/// </summary>
		/// <returns> Number of elements in the array </returns>
		constexpr uint32_t Size() const noexcept;

		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](uint32_t p_data_i) noexcept;

		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](uint32_t p_data_i) const noexcept;

		/// <summary>
		/// Pointer to the array data
		/// </summary>
		/// <returns> pointer to the first element of array data </returns>
		constexpr DATA_T* Data() noexcept;

		constexpr ITERATOR_T begin() noexcept;

		constexpr ITERATOR_T end() noexcept;
	private:
		uint32_t array_s;
		typename std::conditional_t<ARRAY_S == 0, DATA_T*, DATA_T[ARRAY_S]> data_v;
	};

	// -------------------------------------------- Definition -------------------------------------------- //

#	define Arr Array<DATA_T, ARRAY_S, ITERATOR_T>

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	constexpr Arr::Array() noexcept requires(ARRAY_S != 0)
		: array_s(), data_v() {
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	constexpr Arr::Array(uint32_t p_array_s) noexcept requires(ARRAY_S == 0)
		: array_s(p_array_s), data_v((DATA_T*)malloc(p_array_s * sizeof(DATA_T))) {
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	constexpr Arr::~Array() noexcept {
		if constexpr (ARRAY_S == 0) {
			free(this->data_v);
		}
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array size")]]
	constexpr uint32_t Arr::Size() const noexcept {
		if constexpr (ARRAY_S == 0)  return this->array_s;
		else                         return ARRAY_S;
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array element")]]
	constexpr DATA_T& Arr::operator[](uint32_t p_data_i) noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  return ArrayErr::ARRAY_INDEX_OUT_OF_RANGE;
		return this->data_v[p_data_i];
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array element")]]
	constexpr DATA_T& Arr::operator[](uint32_t p_data_i) const noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  return ArrayErr::ARRAY_INDEX_OUT_OF_RANGE;
		return this->data_v[p_data_i];
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array data.")]]
	constexpr DATA_T* Arr::Data() noexcept {
		return this->data_v;
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unsed array begin()")]]
	constexpr ITERATOR_T Arr::begin() noexcept {
		return ITERATOR_T(this->data_v);
	}

	template<class DATA_T, uint32_t ARRAY_S, class ITERATOR_T>
	[[nodiscard("Unused array end()")]]
	constexpr ITERATOR_T Arr::end() noexcept {
		return ITERATOR_T(this->data_v + this->Size());
	}


#	undef Arr

}

#endif // JK_ARRAY_H