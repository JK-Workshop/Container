#include "../Include/Array.h"
#include "../Include/ArrayList.h"
#include "../Include/IndexHeap/IndexHeap.h"
#include <stdio.h>

int main() {
	int a[10] = { 16, 69, 100, 36, 4, 3, 93, 92, 93, 48 };
	auto compare_m = [&a](const uint32_t i, const uint32_t j) { return a[i] < a[j]; };
	JK::IndexHeap<10, decltype(compare_m), JK::IHeapImpl::BINARY_HEAP> ih(compare_m);
	for (uint32_t i = 0; i < 10; ++i) {
		ih << i;
	}
	uint32_t popped_v;
	while(ih.Empty() == false) {
		ih >> popped_v;
		printf("%u ", a[popped_v]);
	}
	printf("\n");

	return 0;
}