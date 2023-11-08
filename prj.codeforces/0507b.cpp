#include <iostream>
#include <cmath>

int main() {
	int r, x, y, x_1, y_1;
	double answer;
	std::cin >> r >> x >> y >> x_1 >> y_1;
	answer = sqrt(pow(x - x_1, 2) + pow(y - y_1, 2));
	std::cout << ceil(answer / 2 / r);
	return 0;
}
