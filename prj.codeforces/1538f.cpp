#include <iostream>

int main() {
	int a;
	std::cin >> a;
	for (int i = 0; i < a; i++) {
		int a, b;
		std::cin >> a >> b;
		int s = b - a;
		while (b > 0) {
			b = b / 10;
			a = a / 10;
			s = s + b - a;
		}
		std::cout << s << std::endl;
	}
}
