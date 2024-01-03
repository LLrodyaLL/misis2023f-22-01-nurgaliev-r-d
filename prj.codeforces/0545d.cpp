#include <iostream>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    int a[n], c = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a, a + n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (s <= a[i]) {
            c++;
            s = s + a[i];
        }
    }
    std::cout << c;
    return 0;
}
