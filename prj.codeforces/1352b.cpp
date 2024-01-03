#include <iostream>

int main() {
	int t; 
	std::cin >> t;
	while (t--) {
		int n, k; 
		std::cin >> n >> k;
		if (n >= k && (n - (k - 1)) % 2 == 1) {
			std::cout << "YES" << "\n";
			for (int i = 1; i <= k - 1; i++) {
				std::cout << 1 << " ";
			}
			std::cout << n - k + 1 << "\n";
		}
		else if (n >= 2 * k && (n - (k - 1) * 2) % 2 == 0) {
			std::cout << "YES" << "\n";
			for (int i = 1; i <= k - 1; i++) {
				std::cout << 2 << " ";
			}
			std::cout << n - 2 * (k - 1) << "\n";
		}
		else std::cout << "NO" << std::endl;
	}
	return 0;
}
