// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

#include <vector>

namespace JK {

	template<class DATA_T, size_t LIST_S = 32, class ITERATOR_T = LinearIterator<DATA_T>>
	class List {
		static_assert(LIST_S > 0, "error: Initial list size must be positive\n");
	private:
		DATA_T* data_v;
		size_t list_c, list_s;

		void grow() noexcept(!JK_DEBUG) {
			// Growth factor = 2
			this->list_s <<= 1;
			this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
			if (this->data_v == nullptr) {
				this->~List();
				JK_DEBUG_BREAK
			}
		}

		void shrink() noexcept(!JK_DEBUG) {
			// Shrink factor = 2
			this->list_s >>= 1;
			this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
			if (this->data_v == nullptr) {
				this->~List();
				JK_DEBUG_BREAK
			}
		}
	public:
		constexpr List() noexcept(!JK_DEBUG)
			: data_v((DATA_T*)malloc(LIST_S * sizeof(DATA_T))), list_c(0), list_s(LIST_S) {
		}

		constexpr ~List() noexcept(!JK_DEBUG) {
			free(this->data_v);
			if constexpr (JK_DEBUG) {
				this->data_v = nullptr;
				this->list_c = this->list_s = 0;
			}
		}

		[[nodiscard("Unused list count")]]
		constexpr size_t Count() const noexcept(!JK_DEBUG) {
			return this->list_c;
		}

		[[nodiscard("Unused list size")]]
		constexpr size_t Size() const noexcept(!JK_DEBUG) {
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

		constexpr void operator<<(const DATA_T& p_data_v) noexcept(!JK_DEBUG) {
			this->data_v[this->list_c++] = p_data_v;
			if (this->list_c >= this->list_s) {
				this->grow();
			}
		}

		constexpr void operator>>(DATA_T& p_data_v) noexcept(!JK_DEBUG) {
			p_data_v = this->data_v[--this->list_c];
			if (this->list_c < (this->list_s >> 1)) {
				this->shrink();
			}
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