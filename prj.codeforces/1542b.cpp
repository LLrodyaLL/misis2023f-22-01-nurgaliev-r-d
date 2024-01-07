#include <iostream>

int main() {
	int ans, a, b, n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int flag = 0;
		std::cin >> ans >> a >> b;
		int t = 1;
		while (t <= ans) {
			if ((ans - t) % b == 0) {
				flag = 1;
			}
			if (ans / t < a || a == 1) {
				break;
			}
			t = t * a;
		}
		if (flag == 1) {
			std::cout << "Yes" << std::endl;
		}
		else {
			std::cout << "No" << std::endl;
		}
	}
	return 0;
}
