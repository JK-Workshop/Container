#include "../Include/Array.h"
#include <iostream>
#include <string>

int main() {
	JK::Array<int, 5> a;
	for (auto& value : a) {
		value = 0;
	}
	uint32_t c;
	std::cin >> c;
	JK::Array<int> b(c);
	printf("%u\n", b.Size());
	for (auto& value : b) {
		value = 1;
	}
	for (auto value : a) {
		std::cout << value << ' ';
	}
	std::cout << '\n';
	for (auto value : b) {
		std::cout << value << ' ';
	}
	return 0;
}