// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

#include <vector>

namespace JK {

	template<class DATA_T, size_t LIST_S, class ITERATOR_T = LinearIterator<DATA_T>>
	class List {
		static_assert(LIST_S > 0, "error: Negative initial list size\n");
	private:
		DATA_T* data_v;
		size_t list_c, list_s;

		constexpr doubleSize() JK_EXCEPT_MODE {
			// Reallocate memotry with doubled size for data_v
		}
	public:
		constexpr List() JK_EXCEPT_MODE
			: data_v(new DATA_T[INIT_LIST_S]), list_c(0), list_s(LIST_S) {
		}

		constexpr ~List() JK_EXCEPT_MODE {
			delete[] data_v;
			if constexpr (JK_DEBUG) {
				list_c = list_s = 0;
			}
		}

		[[nodiscard("Unused list count")]]
		constexpr size_t Count() const noexcept(!JK_DEBUG) {
			return this->list_c;
		}

		[[nodiscard("Unused list size")]]
		constexpr size_t Size() const noexcept(!JK_DEBUG) {
			return -1;
		}

		[[nodiscard("Unused list max size")]]
		constexpr size_t MaxSize() const noexcept(!JK_DEBUG) {
			return this->list_s;
		}

		[[nodiscard("Unused list element")]]
		constexpr DATA_T& operator[](size_t p_data_i) noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}

		[[nodiscard("Unused list element")]]
		constexpr DATA_T& operator[](size_t p_data_i) const noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}

		constexpr void operator<<(DATA_T p_data_v) noexcept(!JK_DEBUG) {
			data_v[list_c] = p_data_v;
			list_c++;
			if (list_c > list_s)
				doubleSize();
		}

		constexpr void operator>>(DATA_T& p_data_v) noexcept(!JK_DEBUG) {
			p_data_v = this->data_v[this->list_c];
			this->list_c--;
		}
		[[nodiscard("Unsed list begin()")]]
		constexpr ITERATOR_T* begin() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v);
		}
		[[nodiscard("Unused list end()")]]
		constexpr ITERATOR_T* end() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v + this->data_c);
		}
	};

}