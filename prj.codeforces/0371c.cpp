#include<iostream>
#include<string>
#include<algorithm>

int main() {
	std::string a;
	std::cin >> a;

	long long nb = 0;
	long long ns = 0;
	long long nc = 0;

	for (int i = 0; i < a.length(); i++) {
		if (a[i] == 'B') {
			nb++;
		}
		else if (a[i] == 'S') {
			ns++;
		}
		else
			nc++;
	}

	long long b, s, c;
	std::cin >> b >> s >> c;

	long long pb, ps, pc;
	std::cin >> pb >> ps >> pc;

	long long money;
	std::cin >> money;

	long long left = 0, right = (long long)1E14;

	long long ans = 0;
	while (left <= right) {
		long long mid = (left + right) / 2;
		long long cb = mid * nb - b;
		long long cs = mid * ns - s;
		long long cc = mid * nc - c;

		if (cb < 0) {
			cb = 0;
		}
		if (cs < 0) {
			cs = 0;
		}
		if (cc < 0) {
			cc = 0;
		}

		long long nm = cb * pb + cs * ps + cc * pc;
		if (nm <= money) {
			ans = mid;
		}
		if (nm > money) {
			right = mid - 1;
		}
		else
			left = mid + 1;
	}

	std::cout << ans;
	return 0;
}
