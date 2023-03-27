#include <iostream>

typedef unsigned long long ull;

const int maxN = 10000;

int t;
ull a, b;
int n;
int m;
int f[maxN * maxN + 100];

ull pow(ull a, ull b, ull p) {
	ull ret = 1 % p;
	a = a % p;
	while (b) {
		if (b & 1) ret = (ret * a) % p;
		a = a * a % p;
		b = b >> 1;
	}
	return ret;
}

void mian() {
	std::cin >> a >> b >> n;
	if (a == 0 || n == 1) {
		std::cout << 0 << '\n';
		return;
	}
	f[0] = 0;
	f[1] = 1;
	f[2] = 1;
	int i = 3;
	while (true) {
		f[i] = (f[i - 2] + f[i - 1]) % n;
		if (f[i - 1] == 1 && f[i] == 1) break;
		i++;
	}
	std::cout << f[pow(a, b, i - 2)] << '\n';
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}