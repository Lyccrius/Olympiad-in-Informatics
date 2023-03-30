#include <iostream>
#include <iomanip>
#include <algorithm>

typedef double dbl;

const int maxN = 30;

int n;
dbl t;
dbl f[maxN + 10];

void mian() {
	f[n] = 1 << n;
	for (int i = n - 1; i >= 0; i--) {
		dbl p0 = std::max(t, (dbl) (1 << i) / f[i + 1]);
		dbl p1 = (p0 - t) / (1 - t);
		dbl p2 = 1 - p1;
		f[i] = (dbl) (1 << i) * p1 + (1 + p0) / 2 * f[i + 1] * p2;
	}
	std::cout << std::setprecision(3) << f[0] << '\n';
	return;
}

int main() {
	std::cout << std::setiosflags(std::ios::fixed);
	while (std::cin >> n >> t && n) mian();
	return 0;
}