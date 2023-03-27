#include <iostream>

const int maxN = 10000;
const int mod = 10001;

int n;
int x[2 * maxN + 10];

bool check(int a, int b) {
	for (int i = 1; i <= n; i++) {
		x[2 * i] = (a * x[2 * i - 1] + b) % mod;
		if (i < n) if ((a * x[2 * i] + b) % mod != x[2 * i + 1]) return false;
	}
	return true;
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> x[2 * i - 1];
	for (int a = 0; a < mod; a++) {
		for (int b = 0; b < mod; b++) {
			if (check(a, b)) {
				for (int i = 1; i <= n; i++) std::cout << x[2 * i] << '\n';
				return 0;
			}
		}
	}
	return 0;
}