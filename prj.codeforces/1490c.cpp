#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int t;
    std::cin >> t;
    std::vector<long long> x(t);

    for (int i = 0; i < t; ++i) {
        std::cin >> x[i];
    }

    for (int i = 0; i < t; ++i) {
        bool found = false;

        for (long long a = 1; a * a * a < x[i]; ++a) {
            long long b = cbrt(x[i] - a * a * a);

            if (b * b * b + a * a * a == x[i]) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "YES" << std::endl;
        }
        else {
            std::cout << "NO" << std::endl;
        }
    }

    return 0;
}
