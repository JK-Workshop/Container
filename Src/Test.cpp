#include <Array.h>
#include <iostream>
#include <string>

int main() {
	JK::Array<int, 3> a;
	a[0] = 0, a[1] = 1, a[2] = 2;
	JK::Array<int> b(5);
	b[0] = 0, b[1] = 1, b[2] = 2, b[3] = 3, b[4] = 4;
	for (auto value : a) {
		std::cout << value << ' ';
	}
	std::cout << '\n';
	for (auto value : b) {
		std::cout << value << ' ';
	}
	return 0;
}