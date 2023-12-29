#include <iostream>
#include <algorithm>

int main()
{
	int t;
	std::cin >> t;
	while (t--) {
		int n;
		std::cin >> n;
		int a[1030] = { 0 };
		for (int i = 1; i <= n; i++) {
			int x;
			std::cin >> x;
			a[x] = i;
		}
		int ans = -1;
		for (int i = 1; i <= 1000; i++)
			for (int j = 1; j <= 1000; j++)
				if (a[i] > 0 && a[j] > 0 && std::__gcd(i, j) == 1) {
					ans = std::max(ans, a[i] + a[j]);
				}
		std::cout << ans << std::endl;
	}
	return 0;
}
