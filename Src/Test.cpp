#include "../Include/Array.h"
#include "../Include/ArrayList.h"
#include "../Include/IndexHeap.h"
#include <stdio.h>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++98-compat"
#endif

int main() {
	int a[5] = { 3, 2, 5, 4, 1 };
	auto heap = JK::Make_IndexHeap<114514u, JK::IHeapImpl::BINARY_HEAP>([&a](uint32_t i, uint32_t j) { return a[i] < a[j]; });
	for (uint32_t i = 0; i < 5; ++i)
		heap << i;
	for (uint32_t i = 0; i < 5; ++i) {
		uint32_t b;
		heap >> b;
		printf("%d ", b);
	}
	printf("\n");

	return 0;
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
