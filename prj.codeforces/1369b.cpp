#include <iostream>

int main() {
    int t, n, dem1, dem0, check, vt, dem, x;
    std::string s;
    std::cin >> t;
    while (t--)
    {
        std::cin >> n >> s;
        std::string h = s;
        s = " " + s;
        dem = 0; vt = 0; dem1 = 0; dem0 = 0; x = 0;
        for (int i = 1; i <= n; i++)
            if (s[i] == '0') {
                dem++;
                }
            else { 
                vt = i;
                break; 
            }
        for (int i = vt; i <= n; i++)
        {
            if (s[i] == '1') {
                x++;
            }
        }
        if (x == n - dem)
        {
            std::cout << h << '\n';
            continue;
        }
        else
        {
            for (int i = n; i >= 1; i--) {
                if (s[i] == '1') {
                    dem1++;
                }
                else {
                    break;
                }
            }
            for (int i = 1; i <= dem + 1; i++) {
                std::cout << '0';
            }
            for (int i = 1; i <= dem1; i++) {
                std::cout << '1';
            }
            std::cout << '\n';
        }
    }
    return 0;
}
