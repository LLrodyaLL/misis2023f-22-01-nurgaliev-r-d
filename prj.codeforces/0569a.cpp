#include <iostream>

int main() {
	int t, s, q, k = 1;
	std::cin >> t >> s >> q;
	while (s * q < t) {
		k += 1;
		s *= q;
	}
	std::cout << k;
}
