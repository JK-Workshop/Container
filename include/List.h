// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include "CompileTime.h"
#include "LinearIterator.h"

namespace JK {

	template<class DATA_T, uint32_t LIST_S = 32, class ITERATOR_T = LinearIterator<DATA_T>>
	class List {
		static_assert(!std::is_class_v<DATA_T>, "Error: Only basic types are accessible, consider class pointer instead.");
		static_assert(LIST_S != 0, "Error: List size should be at least 1.");
	private:
		DATA_T* data_v;
		uint32_t list_c, list_s;
		/// <summary>
		/// Expand list size by a particutlar growth factor
		/// </summary>
		void grow() noexcept(!JK_DEBUG) {
			// Growth factor = 2
			this->list_s <<= 1;
			this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
			[[likely(false)]] if (this->data_v == nullptr) {
				this->~List();
				JK_RT_BREAK
			}
		}
		/// <summary>
		/// Reduce list size by a particular shrink factor
		/// </summary>
		void shrink() noexcept(!JK_DEBUG) {
			// Shrink factor = 2
			this->list_s >>= 1;
			this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
			[[likely(false)]] if (this->data_v == nullptr) {
				this->~List();
				JK_RT_BREAK
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
		/// <summary>
		/// Number of elements currently in the list
		/// </summary>
		/// <returns></returns>
		[[nodiscard("Unused list count")]]
		constexpr uint32_t Count() const noexcept(!JK_DEBUG) {
			return this->list_c;
		}
		/// <summary>
		/// Number of elements the list can currently hold, if its exceeded, the list will grow larger
		/// </summary>
		/// <returns></returns>
		[[nodiscard("Unused list size")]]
		constexpr uint32_t Size() const noexcept(!JK_DEBUG) {
			return this->list_s;
		}
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused list element")]]
		constexpr DATA_T& operator[](uint32_t p_data_i) noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused list element")]]
		constexpr DATA_T& operator[](uint32_t p_data_i) const noexcept(!JK_DEBUG) {
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Push an element to the end of the list
		/// </summary>
		/// <param name="p_data_v"> Value of pushed element </param>
		constexpr void operator<<(const DATA_T& p_data_v) noexcept(!JK_DEBUG) {
			this->data_v[this->list_c++] = p_data_v;
			if (this->list_c >= this->list_s) {
				this->grow();
			}
		}
		/// <summary>
		/// Pop an element from the end of the list
		/// </summary>
		/// <param name="p_data_v"> Value of popped element </param>
		constexpr void operator>>(DATA_T& p_data_v) noexcept(!JK_DEBUG) {
			p_data_v = this->data_v[--this->list_c];
			if (this->list_c < (this->list_s >> 1)) {
				this->shrink();
			}
		}
		[[nodiscard("Unsed list begin()")]]
		constexpr ITERATOR_T begin() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v);
		}
		[[nodiscard("Unused list end()")]]
		constexpr ITERATOR_T end() noexcept(!JK_DEBUG) {
			return ITERATOR_T(this->data_v + this->list_c);
		}
	};

}