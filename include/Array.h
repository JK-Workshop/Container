// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_ARRAY_H)
#define JK_ARRAY_H

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

#define TEMPLATE template<class DATA_T, UintFast_tc auto ARRAY_S, class ITERATOR_T>
#define CLASS_NAME Array<DATA_T, ARRAY_S, ITERATOR_T>

namespace JK {

	template<class DATA_T, UintFast_tc auto ARRAY_S, class ITERATOR_T = LinearIterator<DATA_T>>
	class Array {
	private:
		using Data_t = DATA_T;
		using Size_t = decltype(ARRAY_S);
		constexpr static Size_t Array_s;
		using Iterator_t = ITERATOR_T;
	public:
		constexpr Array() noexcept : data_v() {}
		constexpr ~Array() noexcept {}

		[[nodiscard("Unused array size")]]
		constexpr Size_t Size() const noexcept { return Array_s; }

		[[nodiscard("Unused array data")]]
		constexpr DATA_T* Data() noexcept { return this->data_v; }

		constexpr DATA_T& operator[](const Size_t p_data_i) noexcept;

		constexpr DATA_T& operator[](const Size_t p_data_i) const noexcept;

		[[nodiscard("Unused array iterator begin()")]]
		constexpr ITERATOR_T begin() noexcept { return ITERATOR_T(&this->data_v[0]); }

		[[nodiscard("Unused array iterator end()")]]
		constexpr ITERATOR_T end() noexcept { return ITERATOR_T(&this->data_v[this->Size()]); }
	private:
		DATA_T data_v[Array_s];
	};

	// -------------------------------------------- Definition -------------------------------------------- //

	TEMPLATE [[nodiscard("Unused array element")]]
		constexpr DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  JK_RT_BREAK("Index out of range");
		return this->data_v[p_data_i];
	}

	TEMPLATE [[nodiscard("Unused array element")]]
		constexpr DATA_T& CLASS_NAME::operator[](const CLASS_NAME::Size_t p_data_i) const noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Size())  JK_RT_BREAK("Index out of range");
		return this->data_v[p_data_i];
	}

}

#undef CLASS_NAME
#undef TEMPLATE

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // JK_ARRAY_H
