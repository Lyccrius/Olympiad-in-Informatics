#include <iostream>

const int maxN = 30;

int n;
int f[maxN + 10];
int p[maxN + 10];

int main() {
	f[3] = 1;
	f[4] = 3;
	p[1] = 2;
	p[2] = 4;
	p[3] = 8;
	p[4] = 16;
	for (int i = 5; i <= maxN; i++) {
        p[i] = 2 * p[i - 1];
		f[i] = 2 * f[i - 1] + p[i - 4] - f[i - 4];
	}
	while (std::cin >> n && n) std::cout << f[n] << '\n';
	return 0;
}