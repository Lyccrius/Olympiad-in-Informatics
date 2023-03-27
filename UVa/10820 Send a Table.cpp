#include <iostream>

const int maxN = 5e4;

int n;
int phi[maxN + 10];
int f[maxN + 10];

void init() {
	phi[1] = 1;
	for (int i = 2; i <= maxN; i++) if (!phi[i]) {
		for (int j = i; j <= maxN; j += i) {
			if (!phi[j]) phi[j] = j;
			phi[j] = phi[j] / i * (i - 1);
		}
	}
	f[1] = 1;
	for (int i = 2; i <= maxN; i++) f[i] = f[i - 1] + 2 * phi[i];
	return;
}

void mian() {
	std::cout << f[n] << '\n';
	return;
}

int main() {
	init();
	while (std::cin >> n && n) mian();
	return 0;
}