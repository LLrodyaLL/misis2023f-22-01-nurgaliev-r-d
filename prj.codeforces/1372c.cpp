#include <iostream>

void solve() {
	int n, f = 0, cnt = 0;
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		int tmp;
		std::cin >> tmp;
		if (tmp != i) {
			if (!f) {
				cnt++;
			}
			f = 1;
		}
		else {
			f = 0;
		}
	}
	if (cnt == 0) {
		std::cout << 0 << std::endl;
	}
	else if (cnt == 1) {
		std::cout << 1 << std::endl;
	}
	else {
		std::cout << 2 << std::endl;
	}
}
int main() {
	int t;
	std::cin >> t;
	for (int i = 0; i < t; i++) {
		solve();
	}
	return 0;
}
