#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int N; 
	std::cin >> N;
	std::vector<int> A(N); 
	for (auto& a : A) {
		std::cin >> a;
	}
	std::sort(A.begin(), A.end());
	std::vector<int64_t> dp(N + 1, 0);
	for (int l = 0; l < N; l++) {
		for (int i = 0; i < N - l; i++) {
			dp[i] = std::min(dp[i], dp[i + 1]) + A[i + l] - A[i];
		}
	}
	std::cout << dp[0];
}
