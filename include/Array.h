// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <string.h>

#include "CompileTime.h"

namespace JK {

	template<class ITERATEE_T> class Iterator {

	};

	template<class DATA_T, size_t ARRAY_S, Iterator ITERATOR_V> class Array {

	private:

		constexpr DATA_T data_v[ARRAY_S];

	public:
		/// <summary>
		/// Initialize an empty static array
		/// </summary>
		constexpr Array() JK_EXCEPT_MODE
			: data_v(), iterator() {
		}
		/// <summary>
		/// 
		/// </summary>
		constexpr ~Array() JK_EXCEPT_MODE {
		}
		/// <summary>
		/// Query for the number of elements in the static array
		/// </summary>
		/// <returns> Number of elements in the static array </returns>
		[[nodiscard("Unused array size")]] constexpr size_t Size() const JK_EXCEPT_MODE {
			return ARRAY_S;
		}
		/// <summary>
		/// Access an element through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]] constexpr DATA_T& operator[](size_t p_data_i) JK_EXCEPT_MODE {
			//assert(p_index >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]] constexpr DATA_T& operator[](size_t p_data_i) const JK_EXCEPT_MODE {
			//assert(p_index >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Reset current array with a copy of another array
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(Array& other) const JK_EXCEPT_MODE {
			memcpy(other.data_v, this->data_v, this->Size());
		}

		[[nodiscard("Unsed array begin()")]] constexpr DATA_T* begin() const JK_EXCEPT_MODE {
			return this->data_v;
		}

		[[nodiscard("Unused array end()")]] constexpr DATA_T* end() const JK_EXCEPT_MODE {
			return this->data_v + this->Size();
		}

	};

	template<class DATA_T, size_t ARRAY_S> using Array = Array<DATA_T, ARRAY_T, int>;
}