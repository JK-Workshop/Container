#include <List.h>
#include <iostream>
#include <string>

int main() {
	JK::List<std::string*> strPool;
	int i = 100;
	std::string str = "abc";
	while (i--) {
		std::cout << strPool.Count() << ' ' << strPool.Size() << '\n';
		strPool << &str;
	}
	return 0;
}