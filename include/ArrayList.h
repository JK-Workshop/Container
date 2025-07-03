// Copyright (c) JK Workshop - All rights reserved

#if !defined(JK_ARRAY_LIST_H)
#define JK_ARRAY_LIST_H

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif

#include "CompileTime.h"
#include "Iterator/LinearIterator.h"

namespace JK {

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T = LinearIterator<DATA_T>, JK::UintFast_t SIZE_T = uint32_t>
	class ArrayList {
	public:
		constexpr ArrayList(const SIZE_T p_arrayList_s) noexcept;
		constexpr ~ArrayList() noexcept;
		/// <summary>
		/// Number of elements currently in the list
		/// </summary>
		/// <returns></returns>
		constexpr SIZE_T Count() const noexcept;
		/// <summary>
		/// Number of elements the list can currently hold, if its exceeded, the list will grow larger
		/// </summary>
		/// <returns></returns>
		constexpr SIZE_T Size() const noexcept;
		/// <summary>
		/// Pointer to the first element in the array list
		/// </summary>
		/// <returns> pointer to the first element of array list data </returns>
		constexpr DATA_T* Data() const noexcept;
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](SIZE_T p_data_i) noexcept;
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		constexpr DATA_T& operator[](SIZE_T p_data_i) const noexcept;
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
		SIZE_T arrayList_c, arrayList_s;
		/// <summary>
		/// Expand list size by a particutlar growth factor
		/// </summary>
		constexpr void grow() noexcept;
		/// <summary>
		/// Reduce list size by a particular shrink factor
		/// </summary>
		constexpr void shrink() noexcept;
	};

#define arrayList ArrayList<DATA_T, ITERATOR_T, SIZE_T>

	// ------------------------------------------- Construction ------------------------------------------- //

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T = LinearIterator<DATA_T>, JK::UintFast_t SIZE_T = uint32_t>
	constexpr arrayList Make_ArrayList(const SIZE_T p_arrayList_s) {
		return arrayList(p_arrayList_s);
	}

	// -------------------------------------------- Definition -------------------------------------------- //

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr arrayList::ArrayList(const SIZE_T p_arrayList_s) noexcept
		: data_v((DATA_T*)malloc(p_arrayList_s * sizeof(DATA_T))), arrayList_c(0), arrayList_s(p_arrayList_s) {
		if (data_v == nullptr)  JK_RT_BREAK("Heap allocation failed for array list data")
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr arrayList::~ArrayList() noexcept {
		free(this->data_v);
		if constexpr (JK_DEBUG) {
			this->data_v = nullptr;
			this->arrayList_c = this->arrayList_s = 0;
		}
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused list count")]]
	constexpr SIZE_T arrayList::Count() const noexcept {
		return this->arrayList_c;
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused list size")]]
	constexpr SIZE_T arrayList::Size() const noexcept {
		return this->arrayList_s;
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused array list data")]]
	constexpr DATA_T* arrayList::Data() const noexcept {
		return this->data_v;
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused list element")]]
	constexpr DATA_T& arrayList::operator[](SIZE_T p_data_i) noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Count()) {
				this->~ArrayList();
				JK_RT_BREAK("Index out of range")
			}
		return this->data_v[p_data_i];
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused list element")]]
	constexpr DATA_T& arrayList::operator[](SIZE_T p_data_i) const noexcept {
		if constexpr (JK_DEBUG)
			if (p_data_i >= this->Count()) {
				this->~ArrayList();
				JK_RT_BREAK("Index out of range")
			}
		return this->data_v[p_data_i];
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr void arrayList::operator<<(const DATA_T& p_data_v) noexcept {
		if (this->arrayList_c >= this->arrayList_s)  this->grow();
		this->data_v[this->arrayList_c++] = p_data_v;
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr void arrayList::operator>>(DATA_T& p_data_v) noexcept {
		p_data_v = this->data_v[--this->arrayList_c];
		if (this->arrayList_c < (this->arrayList_s >> 1))  this->shrink();
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unsed list begin()")]]
	constexpr ITERATOR_T arrayList::begin() noexcept {
		return ITERATOR_T(this->data_v);
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	[[nodiscard("Unused list end()")]]
	constexpr ITERATOR_T arrayList::end() noexcept {
		return ITERATOR_T(this->data_v + this->arrayList_c);
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr void arrayList::grow() noexcept {
		// Growth factor = 2
		this->arrayList_s <<= 1;
		this->data_v = (DATA_T*)realloc(this->data_v, this->arrayList_s * sizeof(DATA_T));
		[[unlikely]] if (this->data_v == nullptr) {
			this->~ArrayList();
			JK_RT_BREAK("Heap reallocation failed for array list data")
		}
	}

	template<JK::Fundmtal_t DATA_T, class ITERATOR_T, JK::UintFast_t SIZE_T>
	constexpr void arrayList::shrink() noexcept {
		// Shrink factor = 2
		this->arrayList_s >>= 1;
		this->data_v = (DATA_T*)realloc(this->data_v, this->arrayList_s * sizeof(DATA_T));
		[[unlikely]] if (this->data_v == nullptr) {
			this->~ArrayList();
			JK_RT_BREAK("Heap reallocation failed for array list data")
		}
	}

#undef ArrList

}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // JK_ARRAY_LIST
