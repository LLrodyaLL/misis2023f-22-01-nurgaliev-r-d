#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int x = 0, z = 0, y = 0, f = 0, ans = 0;
        std::string s;
        std::cin >> s;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == '0') {
                x++;
            }
            else {
                z++;
            }
        ans = std::min(x, z);
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '0') {
                f++;
                x--;
            }
            else {
                y++;
                z--;
            }
            ans = std::min(ans, y + x);
            ans = std::min(ans, f + z);
        }
        std::cout << ans << std::endl;
    }
}
