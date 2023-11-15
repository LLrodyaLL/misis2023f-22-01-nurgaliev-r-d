#include <iostream>
#include <algorithm>

int main() {
    long long a[3];
    std::cin >> a[0] >> a[1] >> a[2];
    std::sort(a, a + 3);
    if (a[2] >= 2 * (a[0] + a[1])) {
        std::cout << a[0] + a[1];
    }
    else {
        std::cout << (a[0] + a[1] + a[2]) / 3;
    }
}
