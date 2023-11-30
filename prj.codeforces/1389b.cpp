#include <iostream>
#include <algorithm>

int main()
{
	int t;
	std::cin >> t;
	while (t--)
	{
		int n, k, z, a[100001], s = 0, maxn = 0, ans = 0;;
		std::cin >> n >> k >> z;
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i];
		}
		for (int i = 0; i <= k; ++i)
		{
			if (i + 1 < n) {
				maxn = std::max(maxn, a[i] + a[i + 1]);
			}
			s += a[i];
			if ((k - i) % 2 == 0)
			{
				int te = (k - i) / 2;
				if (te <= z) {
					ans = std::max(ans, s + te * maxn);
				}
			}
		}
		std::cout << ans << std::endl;
	}
	return 0;
}
