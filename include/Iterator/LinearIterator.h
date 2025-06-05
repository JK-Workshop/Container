#pragma once

#include "CompileTime.h"

namespace JK {

	/// <summary>
	/// Iterator for linear structure such as array, list, linked list etc.
	/// </summary>
	/// <typeparam name="DATA_T"> type of element in linear data structure </typeparam>
	template<class DATA_T>
	class LinearIterator {
	private:
		DATA_T* tracker_ptr;
	public:
		constexpr LinearIterator(DATA_T* p_tracker_ptr) noexcept(!JK_DEBUG)
			: tracker_ptr(p_tracker_ptr) {
		}
		constexpr LinearIterator(const LinearIterator& other) noexcept(!JK_DEBUG)
			: tracker_ptr(other.tracker_ptr) {
		}
		constexpr ~LinearIterator() noexcept(!JK_DEBUG) {
		}
		constexpr DATA_T& operator*() const noexcept(!JK_DEBUG) {
			return *this->tracker_ptr;
		}
		constexpr DATA_T* operator->() const noexcept(!JK_DEBUG) {
			return this->tracker_ptr;
		}
		constexpr  DATA_T& operator[](uint32_t p_data_i) const noexcept(!JK_DEBUG) {
			return tracker_ptr[p_data_i];
		}
		constexpr LinearIterator& operator++() noexcept(!JK_DEBUG) {
			this->tracker_ptr++;
			return *this;
		}
		constexpr LinearIterator& operator--() noexcept(!JK_DEBUG) {
			this->tracker_ptr--;
			return *this;
		}
		[[nodiscard("Unused incremented value, use prefix operator++ instead")]]
		constexpr LinearIterator operator++(int) noexcept(!JK_DEBUG) {
			LinearIterator Iterator_tmp = *this;
			this->tracker_ptr++;
			return Iterator_tmp;
		}
		[[nodiscard("Unused decremented value, use prefix operator-- instead")]]
		constexpr LinearIterator operator--(int) noexcept(!JK_DEBUG) {
			LinearIterator Iterator_tmp = *this;
			this->tracker_ptr--;
			return Iterator_tmp;
		}
		constexpr bool operator==(const LinearIterator& p_other) const noexcept(!JK_DEBUG) {
			return this->tracker_ptr == p_other.tracker_ptr;
		}
		constexpr bool operator!=(const LinearIterator& p_other) const noexcept(!JK_DEBUG) {
			return this->tracker_ptr != p_other.tracker_ptr;
		}
	};

}