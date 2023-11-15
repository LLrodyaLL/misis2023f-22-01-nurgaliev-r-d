#include <iostream>

int main() {
	long long n, s;
	std::cin >> n >> s;
	if (s >= 2 * n) {
		std::cout << "YES" << std::endl;
		for (int i = 1; i < n; i++) {
			std::cout << "1 ";
		}
		std::cout << s - n + 1 << std::endl << s / 2;
	}
	else {
		std::cout << "NO";
	}
}
