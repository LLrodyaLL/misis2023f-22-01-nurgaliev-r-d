#include <iostream>

int a[505], b[505];
int main()
{
	int t; 
	std::cin >> t;
	while (t--)
	{
		int n, i; 
		std::cin >> n;
		for (i = 1; i <= n; i++)
			std::cin >> a[i];
		for (i = 1; i <= n; i++)
			std::cin >> b[i];
		int q = 0, w = 0, flag = 1;
		for (i = 1; i <= n; i++)
		{
			if (b[i])
				q = 1;
			else
				w = 1;
			if (a[i - 1] > a[i])
				flag = 0;
		}

		if (flag) 
			std::cout << "YES";

		else if (q && w) 
			std::cout << "YES";


		else 
			std::cout << "NO";

		std::cout << std::endl;
	}
	return 0;
}
