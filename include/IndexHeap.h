// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "CompileTime.h"

namespace JK {

	template<uint32_t HEAP_S, bool(*COMPARE)(const uint32_t i, const uint32_t j)>
	class IndexHeap {
		static_assert(HEAP_S >= 0, "Heap size can't be negative.");
	private:
		uint32_t data_c;
		uint32_t data_v[HEAP_S + 1];
		uint32_t hash_v[HEAP_S];

		constexpr void update(uint32_t p_target_i) {

		}

		constexpr void downdate(uint32_t p_target_i) {

		}
	public:
		constexpr IndexHeap() noexcept
			: data_c(1), data_v() {

		}
		constexpr ~IndexHeap() noexcept {

		}

		[[nodiscard("Unused heap size.")]]
		constexpr uint32_t Size() const noexcept {
			return HEAP_S;
		}

		constexpr uint32_t Top() {

		}

		constexpr void operator<<(uint32_t p_target_v) {
			
		}

		constexpr void operator>>() {

		}

		constexpr void operator>>(uint32_t& p_target_v) {

		}
		
		constexpr uint32_t& operator[](uint32_t p_target_v) {

		}
	};

}
