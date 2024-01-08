#include <iostream>
#include <algorithm>

int main() {
    int t;
    long long n, r, a;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> n >> r;
        a = std::min(n - 1, r);
        std::cout << a * (a + 1) / 2 + (r >= n) << std::endl;
    }
    return 0;
}
