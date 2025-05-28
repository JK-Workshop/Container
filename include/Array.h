// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <string.h>

#include "CompileTime.h"

namespace JK {

	template<class DATA_T, size_t ARRAY_S, class ITERATOR_T = iterator>
	class Array {

	private:
		static class iterator {
		private:
			DATA_T* tracker_ptr;
		public:

			constexpr iterator(DATA_T* p_tracker_ptr) JK_EXCEPT_MODE
				: tracker_ptr(p_tracker_ptr) {
				
			}

			constexpr ~iterator() JK_EXCEPT_MODE {

			}

			constexpr DATA_T& operator*() const JK_EXCEPT_MODE {
				return *this->tracker_ptr;
			}

			constexpr DATA_T* operator->() const JK_EXCEPT_MODE {
				return this->tracker_ptr;
			}

			constexpr DATA_T& operator[](size_t p_data_i) const JK_EXCEPT_MODE {
				return tracker_ptr[p_data_i];
			}

			constexpr iterator& operator++() JK_EXCEPT_MODE {
				this->tracker_ptr++;
				return *this;
			}

			constexpr iterator operator++(int) JK_EXCEPT_MODE {
				iterator tmpIterator = *this;
				this->tracker_ptr++;
				return tmpIterator;
			}

			constexpr iterator& operator--() JK_EXCEPT_MODE {
				this->tracker_ptr--;
				return *this;
			}

			constexpr iterator operator--(int) JK_EXCEPT_MODE {
				iterator tmpIterator = *this;
				this->tracker_ptr--;
				return tmpIterator;
			}

			constexpr bool operator==(interator& p_other) {
				return this->tracker_ptr == p_other.tracker_ptr;
			}

			constexpr bool operator!=(interator& p_other) {
				return this->tracker_ptr != p_other.tracker_ptr;
			}
		};

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
			JK_VERIFY(p_data_i >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Const access an elemetns through index
		/// </summary>
		/// <param name="p_data_i"> Index of element to be accessed </param>
		/// <returns> Value of accessed element </returns>
		[[nodiscard("Unused array element")]] constexpr DATA_T& operator[](size_t p_data_i) const JK_EXCEPT_MODE {
			JK_VERIFY(p_data_i >= this->Size(), "Index out of bound\n");
			return this->data_v[p_data_i];
		}
		/// <summary>
		/// Reset current array with a copy of another array
		/// </summary>
		/// <param name="other"></param>
		constexpr void operator=(Array& other) const JK_EXCEPT_MODE {
			memcpy(other.data_v, this->data_v, this->Size());
		}

		[[nodiscard("Unsed array begin()")]] constexpr ITERATOR_T begin() const JK_EXCEPT_MODE {
			return ITERATOR_T(this->data_v);
		}

		[[nodiscard("Unused array end()")]] constexpr ITERATOR_T end() const JK_EXCEPT_MODE {
			return ITERATOR_T(this->data_v + this->Size());
		}

	};
}