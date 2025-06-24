// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_ARRAY_LIST_H)
#define JK_ARRAY_LIST_H

#include "CompileTime/UniversalCT.h"
#include "Iterator/LinearIterator.h"

namespace JK {

	template<Fundmtal_t DATA_T, uint32_t LIST_S = 32, class ITERATOR_T = LinearIterator<DATA_T>>
	class ArrayList {
		static_assert(LIST_S != 0, "Error: List size should be at least 1.");
	public:
		constexpr ArrayList() noexcept;

		constexpr ~ArrayList() noexcept;

		/// <summary>
		/// Number of elements currently in the list
		/// </summary>
		/// <returns></returns>
		constexpr uint32_t Count() const noexcept;

		/// <summary>
		/// Number of elements the list can currently hold, if its exceeded, the list will grow larger
		/// </summary>
		/// <returns></returns>
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
		/// Push an element to the end of the list
		/// </summary>
		/// <param name="p_data_v"> Value of pushed element </param>
		constexpr void operator<<(const DATA_T& p_data_v) noexcept;

		/// <summary>
		/// Pop an element from the end of the list
		/// </summary>
		/// <param name="p_data_v"> Value of popped element </param>
		constexpr void operator>>(DATA_T& p_data_v) noexcept;

		constexpr ITERATOR_T begin() noexcept;

		constexpr ITERATOR_T end() noexcept;
	private:
		DATA_T* data_v;
		uint32_t list_c, list_s;

		/// <summary>
		/// Expand list size by a particutlar growth factor
		/// </summary>
		constexpr void grow() noexcept;

		/// <summary>
		/// Reduce list size by a particular shrink factor
		/// </summary>
		constexpr void shrink() noexcept;
	};

	// -------------------------------------------- Definition -------------------------------------------- //

#	define ArrList ArrayList<DATA_T, LIST_S, ITERATOR_T>

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr ArrList::ArrayList() noexcept
		: data_v((DATA_T*)malloc(LIST_S * sizeof(DATA_T))), list_c(0), list_s(LIST_S) {
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr ArrList::~ArrayList() noexcept {
		free(this->data_v);
		if constexpr (JK_DEBUG) {
			this->data_v = nullptr;
			this->list_c = this->list_s = 0;
		}
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unused list count")]]
	constexpr uint32_t ArrList::Count() const noexcept {
		return this->list_c;
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unused list size")]]
	constexpr uint32_t ArrList::Size() const noexcept {
		return this->list_s;
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unused list element")]]
	constexpr DATA_T& ArrList::operator[](uint32_t p_data_i) noexcept {
		return this->data_v[p_data_i];
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unused list element")]]
	constexpr DATA_T& ArrList::operator[](uint32_t p_data_i) const noexcept {
		return this->data_v[p_data_i];
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr void ArrList::operator<<(const DATA_T& p_data_v) noexcept {
		this->data_v[this->list_c++] = p_data_v;
		if (this->list_c >= this->list_s)  this->grow();
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr void ArrList::operator>>(DATA_T& p_data_v) noexcept {
		p_data_v = this->data_v[--this->list_c];
		if (this->list_c < (this->list_s >> 1))  this->shrink();
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unsed list begin()")]]
	constexpr ITERATOR_T ArrList::begin() noexcept {
		return ITERATOR_T(this->data_v);
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	[[nodiscard("Unused list end()")]]
	constexpr ITERATOR_T ArrList::end() noexcept {
		return ITERATOR_T(this->data_v + this->list_c);
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr void grow() noexcept {
		// Growth factor = 2
		this->list_s <<= 1;
		this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
		[[unlikely]] if (this->data_v == nullptr) {
			this->~ArrayList();
			JK_RT_BREAK
		}
	}

	template<Fundmtal_t DATA_T, uint32_t LIST_S, class ITERATOR_T>
	constexpr void shrink() noexcept {
		// Shrink factor = 2
		this->list_s >>= 1;
		this->data_v = (DATA_T*)realloc(this->data_v, this->list_s * sizeof(DATA_T));
		[[unlikely]] if (this->data_v == nullptr) {
			this->~ArrayList();
			JK_RT_BREAK
		}
	}

#	undef ArrList

}

#endif // JK_ARRAY_LIST