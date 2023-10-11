#include <iostream>
#include <string>

int main() {
    std::string n;
    std::cin >> n;

    int len = n.length();
    bool found = false;
    std::string result;

    for (int i = 0; i < len; i++) {
        if ((n[i] - '0') % 8 == 0) {
            result = n[i];
            found = true;
            break;
        }
        for (int j = i + 1; j < len; j++) {
            if ((10 * (n[i] - '0') + (n[j] - '0')) % 8 == 0) {
                result = n[i];
                result += n[j];
                found = true;
                break;
            }
            for (int k = j + 1; k < len; k++) {
                if ((100 * (n[i] - '0') + 10 * (n[j] - '0') + (n[k] - '0')) % 8 == 0) {
                    result = n[i];
                    result += n[j];
                    result += n[k];
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (found) {
        std::cout << "YES" << std::endl;
        std::cout << result;
    }
    else {
        std::cout << "NO";
    }

    return 0;
}
