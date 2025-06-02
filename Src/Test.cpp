#include "../Include/List.h"
#include <iostream>
#include <string>

int main() {
	JK::List<float, 1> strPool;
	int i = 100;
	while (i--) {
		std::cout << strPool.Count() << ' ' << strPool.Size() << '\n';
		strPool << 1.0f;
	}
	for (auto value : strPool) {
		std::cout << value;
	}
	return 0;
}