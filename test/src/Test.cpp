#include <iostream>
#include <string>

#include <Array.h>
#include <array>

int main() {

	JK::Array<std::string, 3> a;
	a[0] = "Sparc";
	a[1] = "Th1ap";
	a[2] = "Nyansky";

	for (auto& value : a) {
		std::cout << value << ' ';
	}

	printf("\n");

	std::array<std::string, 3> b;
	b[0] = "Sparc";
	b[1] = "Th1ap";
	b[2] = "Nyansky";

	for (auto& value : b) {
		std::cout << value << ' ';
	}

	return 0;
}