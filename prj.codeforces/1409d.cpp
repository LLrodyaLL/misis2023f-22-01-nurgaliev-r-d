#include <iostream>

int sum(long long n) {
    int steps = 0;
    while (n > 0) {
        steps += n % 10;
        n /= 10;
    }
    return steps;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        long long n;
        int s;
        std::cin >> n >> s;
        long long steps = 0;
        if (sum(n) <= s) {
            std::cout << 0 << std::endl;
            continue;
        }
        long long gg = 1;
        for (int i = 0; i < 18; ++i) {
            int digit = (n / gg) % 10;
            long long add = gg * ((10 - digit) % 10);
            n += add;
            steps += add;
            if (sum(n) <= s) {
                break;
            }
            gg *= 10;
        }
        std::cout << steps << std::endl;
    }
    return 0;
}
