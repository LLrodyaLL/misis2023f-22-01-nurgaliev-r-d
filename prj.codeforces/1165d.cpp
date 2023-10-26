#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	long long int t, n, i, c, d[1000], p, c1;
	std::cin >> t;
	while (t--)
	{
		std::cin >> n;
		c = 0, c1 = 0;
		for (i = 0; i < n; i++)
			std::cin >> d[i];
		std::sort(d, d + n);
		p = d[0] * d[n - 1];
		for (i = 0; i < n; i++)
		{
			if (p % d[i] == 0)
				c1++;
		}
		for (i = 2; i * i <= p; i++)
		{
			if (p % i == 0)
			{
				if (i * i == p)
					c++;
				else
					c += 2;
			}
		}
		if (c == n && c1 == n)
			std::cout << p << std::endl;
		else
			std::cout << -1 << std::endl;
	}
	return 0;
}
