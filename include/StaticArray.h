// Copyright (C) JK Workshop - All rights reserved

#pragma once

#include <stdint.h>
#include <string.h>

#define JK_STACK_ALLOCATE 0
#define JK_HEAP_ALLOCATE  1

#define JK_DEBUG 0

namespace JK {

	template<class ITERATEE_T> class Iterator {

	};

	template<class DATA_T, size_t ARRAY_S, class ITERATOR> class StaticArray {

	private:

		constexpr DATA_T data_v[ARRAY_S];

		ITERATOR iterator;

	public:
		/// <summary>
		/// Initialize an empty static array
		/// </summary>
		constexpr StaticArray()
			: data_v(), iterator() {
		}
		/// <summary>
		/// 
		/// </summary>
		constexpr ~StaticArray() {
		}
		/// <summary>
		/// Query for the number of elements in the static array
		/// </summary>
		/// <returns> Number of elements in the static array </returns>
		[[nodiscard("Unused static array size")]] constexpr size_t Size() const {
			return ARRAY_S;
		}
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused static array element")]] constexpr DATA_T& operator[](size_t p_data_i) {
			//assert(p_index >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused static array element")]] constexpr DATA_T& operator[](size_t p_data_i) const {
			//assert(p_index >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Refill current static array with copy of another array
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(StaticArray& other) const {
			memcpy(other.data_v, this->data_v, this->Size());
		}

		// TODO: Inplement operator= with other being dynamic array, heap, linked list, BST etc.

		[[nodiscard("Unsed static array begin()")]] constexpr DATA_T* begin() const {
			return this->data_v;
		}

		[[nodiscard("Unused static array end()")]] constexpr DATA_T* end() const {
			return this->data_v + this->Size();
		}

	};

	//template<class TYPE, size_t SIZE>
	//using StaticArray_ = StaticArray<TYPE, SIZE, JK_STACK_ALLOCATION, int>;
}