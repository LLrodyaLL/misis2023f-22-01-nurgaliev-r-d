#include <iostream>
#include <algorithm>
#include <string>

int main()
{
	int t;
	std::cin >> t;
	while (t--)
	{
		std::string s;
		std::cin >> s;
		int answer = 0;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				int l = 0, c = i;
				for (int k = 0; k < s.size(); k++) {
					if (s[k] == c + '0') {
						l++;
						c = (c == i) ? j : i;
					}
				}
				if (i != j && (l & 1)) --l;
				answer = std::max(answer, l);
			}
		std::cout << s.size() - answer << std::endl;
	}
}
