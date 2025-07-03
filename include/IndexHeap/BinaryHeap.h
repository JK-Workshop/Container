// Copyright (c) JK Workshop - All rights reserved

#include <stdlib.h>
#include <string.h>

#include "../IndexHeap.h"

namespace JK {

#define indexHeap IndexHeap<HEAP_S, JK::IHeapImpl::BINARY_HEAP, COMPARATOR_T>

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	class indexHeap {
		using SIZE_T = decltype(HEAP_S);
	public:
		constexpr IndexHeap(COMPARATOR_T&& p_comparator_m) noexcept;

		constexpr ~IndexHeap() noexcept;
		/// <summary>
		/// Size of heap
		/// </summary>
		/// <returns> size of heap </returns>
		constexpr SIZE_T Size() const noexcept;
		/// <summary>
		/// Whether or not the heap is empty
		/// </summary>
		/// <returns> true if it's empty, false otherwise </returns>
		constexpr bool IsEmpty() const noexcept;
		/// <summary>
		/// Value at the top of heap
		/// </summary>
		/// <returns> value at the top of heap, in JK_DEBUG mode, returns -1 if heap is empty </returns>
		constexpr SIZE_T Top() const noexcept;
		/// <summary>
		/// Push a value into heap
		/// </summary>
		/// <param name="p_target_v"> value to be pushed </param>
		/// <returns> At JK_DEBUG mode, return HEAP_FULL if pushing to a full heap, HEAP_SUCCESS instead </returns>
		constexpr void operator<<(const SIZE_T p_target_v) noexcept;
		/// <summary>
		/// Pop and return a value from heap
		/// </summary>
		/// <param name="p_target_v"> holds popped value </param>
		/// <returns> At JK_DEBUG mode, return HEAP_EMPTY if poping from an empty heap, HEAP_SUCCESS instead </returns>
		constexpr void operator>>(SIZE_T& p_target_v) noexcept;
		/// <summary>
		/// Pop a value from heap
		/// </summary>
		constexpr void Pop() noexcept;
		/// <summary>
		/// Update the heap only if a value "decreased"
		/// </summary>
		/// <param name="p_target_v"> value that "decreased" </param>
		/// <returns> At JK_DEBUG mode, return HEAP_VALUE_NOT_FOUND if updating a value not in the heap </returns>
		constexpr void Update(const SIZE_T p_target_v) noexcept;
	private:
		SIZE_T data_c;
		SIZE_T data_v[HEAP_S + 1];
		SIZE_T hash_v[HEAP_S];
		COMPARATOR_T comparator_m;
		/// <summary>
		/// Update logic
		/// </summary>
		/// <param name="p_target_i"> index of heap node to be updated </param>
		constexpr void update(SIZE_T p_target_i) noexcept;
		/// <summary>
		/// Downdate logic
		/// </summary>
		/// <param name="p_target_i"> index of heap node to be downdated </param>
		constexpr void downdate(SIZE_T p_target_i) noexcept;
	};

	// -------------------------------------------- Definition -------------------------------------------- //

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr indexHeap::IndexHeap(COMPARATOR_T&& p_comparator_m) noexcept
		: data_c(0), data_v(), hash_v(), comparator_m(std::forward<COMPARATOR_T>(p_comparator_m)) {
		// Set all hash result to 0 for later error detection
		if (JK_DEBUG)  memset(hash_v, 0, HEAP_S);
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr indexHeap::~IndexHeap() noexcept {}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	[[nodiscard("Unused heap size.")]]
	constexpr indexHeap::SIZE_T indexHeap::Size() const noexcept { return HEAP_S; }

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	[[nodiscard("Unused heap empty query.")]]
	constexpr bool indexHeap::IsEmpty() const noexcept { return this->data_c == 0; }

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	[[nodiscard("Unused heap top.")]]
	constexpr indexHeap::SIZE_T indexHeap::Top() const noexcept {
		if constexpr (JK_DEBUG)
			if (this->IsEmpty()) {
				this->~IndexHeap();
				JK_RT_BREAK("Unable to query the Top of an empty heap")
			}
		return this->data_v[1];
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::operator<<(const indexHeap::SIZE_T p_target_v) noexcept {
		if constexpr (JK_DEBUG)
			if (this->data_c == this->Size()) {
				this->~IndexHeap();
				JK_RT_BREAK("Unable to Push into a full heap")
			}
		++data_c;
		this->data_v[this->data_c] = p_target_v;
		this->update(this->data_c);
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::operator>>(indexHeap::SIZE_T& p_target_v) noexcept {
		p_target_v = this->Top();
		this->Pop();
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::Pop() noexcept {
		if constexpr (JK_DEBUG)  this->hash_v[this->Top()] = 0;
		this->data_v[1] = this->data_v[this->data_c];
		--this->data_c;
		this->downdate(1);
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::Update(const indexHeap::SIZE_T p_target_v) noexcept {
		if constexpr (JK_DEBUG)
			if (this->hash_v[p_target_v] == 0) {
				this->~IndexHeap();
				JK_RT_BREAK("Unable to Update an nonexist heap element")
			}
		this->update(this->hash_v[p_target_v]);
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::update(indexHeap::SIZE_T p_target_i) noexcept {
		SIZE_T this_v = this->data_v[p_target_i];
		SIZE_T up_i = p_target_i >> 1;  // parent of p_target_i
		while (up_i != 0) {             // as long as not reaching the top
			if (this->comparator_m(this_v, this->data_v[up_i])) {
				this->hash_v[
					this->data_v[p_target_i] = this->data_v[up_i]
				] = p_target_i;         // bubble up_i down
				p_target_i = up_i;
				up_i >>= 1;
			}
			else  break;
		}
		this->hash_v[
			this->data_v[p_target_i] = this_v
		] = p_target_i;
	}

	template<JK::UintFast_t auto HEAP_S, class COMPARATOR_T>
	constexpr void indexHeap::downdate(indexHeap::SIZE_T p_target_i) noexcept {
		SIZE_T this_v = this->data_v[p_target_i];
		SIZE_T down_i = p_target_i << 1;    // "smaller" child of p_target_i
		SIZE_T last_i = this->data_c >> 1;  // last non-leaf node
		while (p_target_i <= last_i) {      // as long as not reaching the bottom
			down_i += this->comparator_m(this->data_v[down_i + 1], this->data_v[down_i]);  // the smaller one
			if (this->comparator_m(this->data_v[down_i], this_v)) {  // even the "smaller" one is "larger"
				this->hash_v[
					this->data_v[p_target_i] = this->data_v[down_i]
				] = p_target_i;             // bubble down_i up
				p_target_i = down_i;
				down_i <<= 1;
			}
			else  break;
		}
		this->hash_v[
			this->data_v[p_target_i] = this_v
		] = p_target_i;
	}

#undef indexHeap

}
