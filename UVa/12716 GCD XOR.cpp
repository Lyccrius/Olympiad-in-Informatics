#include <iostream>

const int maxN = 3e7;

int t;
int n;
int ans[maxN + 10];

void init() {
	for (int c = 1; c <= maxN; c++) {
		for (int a = c * 2; a <= maxN; a += c) {
			int b = a - c;
			if ((a ^ b) == c) ans[a]++;
		}
	}
	for (int i = 1; i <= maxN; i++) ans[i] += ans[i - 1];
	return;
}

void mian() {
	std::cin >> n;
	std::cout << ans[n] << '\n';
	return;
}

int main() {
	init();
	std::cin >> t;
	for (int kase = 1; kase <= t; kase++) std::cout << "Case " << kase << ": ", mian();
	return 0;
}