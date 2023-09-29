#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, q;
    std::cin >> n;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end()); 

    std::cin >> q;
    std::vector<int> m(q);
    for (int j = 0; j < q; j++) {
        std::cin >> m[j];
    }

    for (auto now : m) {
        int k = std::upper_bound(x.begin(), x.end(), now) - x.begin(); 
        std::cout << k << " ";
    }

    return 0;
}
