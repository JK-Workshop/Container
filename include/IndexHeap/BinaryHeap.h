// Copyright (c) JK Workshop - All rights reserved

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "CompileTime/UniversalCT.h"
#include "IndexHeap.h"

namespace JK {

#	define IHeap IndexHeap<HEAP_S, COMPARE_T, IHeapImpl::BINARY_HEAP>

	template<uint32_t HEAP_S, class COMPARE_T>
	class IHeap {
		static_assert(HEAP_S >= 0, "Heap size can't be negative.");
	public:
		constexpr IndexHeap(COMPARE_T p_compare_m) noexcept;
		constexpr ~IndexHeap() noexcept;
		/// <summary>
		/// Size of heap
		/// </summary>
		/// <returns> size of heap </returns>
		constexpr uint32_t Size() const noexcept;
		/// <summary>
		/// Whether or not the heap is empty
		/// </summary>
		/// <returns> true if it's empty, false otherwise </returns>
		constexpr bool Empty() const noexcept;
		/// <summary>
		/// Value at the top of heap
		/// </summary>
		/// <returns> value at the top of heap, in JK_DEBUG mode, returns -1 if heap is empty </returns>
		constexpr uint32_t Top() const noexcept;
		/// <summary>
		/// Push a value into heap
		/// </summary>
		/// <param name="p_target_v"> value to be pushed </param>
		/// <returns> At JK_DEBUG mode, return HEAP_FULL if pushing to a full heap, HEAP_SUCCESS instead </returns>
		constexpr JK_DEBUG_ERR_T(IHeapErr) operator<<(uint32_t p_target_v) noexcept;
		/// <summary>
		/// Pop and return a value from heap
		/// </summary>
		/// <param name="p_target_v"> holds popped value </param>
		/// <returns> At JK_DEBUG mode, return HEAP_EMPTY if poping from an empty heap, HEAP_SUCCESS instead </returns>
		constexpr JK_DEBUG_ERR_T(IHeapErr) operator>>(uint32_t& p_target_v) noexcept;
		
		//constexpr JK_DEBUG_ERR_T Pop() noexcept;
		/// <summary>
		/// Update the heap only if a value "decreased"
		/// </summary>
		/// <param name="p_target_v"> value that "decreased" </param>
		/// <returns> At JK_DEBUG mode, return HEAP_VALUE_NOT_FOUND if updating a value not in the heap </returns>
		constexpr JK_DEBUG_ERR_T(IHeapErr) Update(uint32_t p_target_v) noexcept;

	private:
		uint32_t data_c;
		uint32_t data_v[HEAP_S + 1];
		uint32_t hash_v[HEAP_S];
		COMPARE_T compare_m;
		/// <summary>
		/// Update logic
		/// </summary>
		/// <param name="p_target_i"> index of heap node to be updated </param>
		constexpr void update(uint32_t p_target_i);
		/// <summary>
		/// Downdate logic
		/// </summary>
		/// <param name="p_target_i"> index of heap node to be downdated </param>
		constexpr void downdate(uint32_t p_target_i);
	};

	// -------------------------------------------- Definition -------------------------------------------- //

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr IHeap::IndexHeap(COMPARE_T p_compare_m) noexcept
		: data_c(0), data_v(), hash_v(), compare_m(p_compare_m) {
		// Set all hash result to 0 for later error detection
		if (JK_DEBUG)  memset(hash_v, 0, HEAP_S);
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr IHeap::~IndexHeap() noexcept {}

	template<uint32_t HEAP_S, class COMPARE_T>
	[[nodiscard("Unused heap size.")]]
	constexpr uint32_t IHeap::Size() const noexcept { return HEAP_S; }

	template<uint32_t HEAP_S, class COMPARE_T>
	[[nodiscard("Unused heap empty query.")]]
	constexpr bool IHeap::Empty() const noexcept { return this->data_c == 0; }

	template<uint32_t HEAP_S, class COMPARE_T>
	[[nodiscard("Unused heap top.")]]
	constexpr uint32_t IHeap::Top() const noexcept {
		//if constexpr (JK_DEBUG)
			//if (this->data_c == 1)  return IHeapErr::IHEAP_EMPTY;
		return this->data_v[1];
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr JK_DEBUG_ERR_T(IHeapErr) IHeap::operator<<(uint32_t p_target_v) noexcept {
		if constexpr (JK_DEBUG)
			if (this->data_c == this->Size())  return IHeapErr::IHEAP_FULL;
		++data_c;
		this->data_v[this->data_c] = p_target_v;
		this->update(this->data_c);
		if constexpr (JK_DEBUG)  return IHeapErr::IHEAP_SUCCESS;
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr JK_DEBUG_ERR_T(IHeapErr) IHeap::operator>>(uint32_t& p_target_v) noexcept {
		if constexpr (JK_DEBUG) {
			if (this->Empty())  return IHeapErr::IHEAP_EMPTY;
			this->hash_v[this->Top()] = 0;
		}
		p_target_v = this->Top();
		this->data_v[1] = this->data_v[this->data_c];
		--this->data_c;
		this->downdate(1);
		if constexpr (JK_DEBUG)  return IHeapErr::IHEAP_SUCCESS;
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr JK_DEBUG_ERR_T(IHeapErr) IHeap::Update(uint32_t p_target_v) noexcept {
		if constexpr (JK_DEBUG)
			if (this->hash_v[p_target_v] == 0)  return IHeapErr::IHEAP_VALUE_NOT_FOUND;
		this->update(this->hash_v[p_target_v]);
		if constexpr (JK_DEBUG)  return IHeapErr::IHEAP_SUCCESS;
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr void IHeap::update(uint32_t p_target_i) {
		uint32_t this_v = this->data_v[p_target_i];
		uint32_t up_i = p_target_i >> 1;  // parent of p_target_i
		while (up_i != 0) {  // as long as not reaching the top
			if (this->compare_m(this_v, this->data_v[up_i])) {
				this->hash_v[
					this->data_v[p_target_i] = this->data_v[up_i]
				] = p_target_i;  // bubble up_i down
				p_target_i = up_i;
				up_i >>= 1;
			}
			else  break;
		}
		this->hash_v[
			this->data_v[p_target_i] = this_v
		] = p_target_i;
	}

	template<uint32_t HEAP_S, class COMPARE_T>
	constexpr void IHeap::downdate(uint32_t p_target_i) {
		uint32_t this_v = this->data_v[p_target_i];
		uint32_t down_i = p_target_i << 1;    // "smaller" child of p_target_i
		uint32_t last_i = this->data_c >> 1;  // last non-leaf node
		while (p_target_i <= last_i) {  // as long as not reaching the bottom
			down_i += this->compare_m(this->data_v[down_i + 1], this->data_v[down_i]);  // the smaller one
			if (this->compare_m(this->data_v[down_i], this_v)) {  // even the "smaller" one is "larger"
				this->hash_v[
					this->data_v[p_target_i] = this->data_v[down_i]
				] = p_target_i;  // bubble down_i up
				p_target_i = down_i;
				down_i <<= 1;
			}
			else  break;
		}
		this->hash_v[
			this->data_v[p_target_i] = this_v
		] = p_target_i;
	}

#	undef IHeap

}