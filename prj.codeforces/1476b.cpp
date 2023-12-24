#include <iostream>

int main() {
    long long t, n, k;
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        long long init, sum = 0;
        std::cin >> init;
        for (long long p = 1; p < n; p++) {
            long long x; 
            std::cin >> x;
            if (100 * x > k * (init + sum)) {
                sum = (100 * x - k * init + (k - 1)) / k; 
            }
            init += x;
        }
        std::cout << sum << "\n";
    }
    return 0;
}
