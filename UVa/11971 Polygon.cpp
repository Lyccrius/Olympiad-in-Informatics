#include <iostream>

typedef long long lxl;

int t;
int n, k;

lxl gcd(lxl a, lxl b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void mian() {
	std::cin >> n >> k;
	lxl a = k + 1;
	lxl b = 1ll << k;
	lxl g = gcd(a, b);
	a /= g;
	b /= g;
	std::cout << (b - a) << '/' << b << '\n';
	return;
}

int main() {
	std::cin >> t;
	for (int kase = 1; kase <= t; kase++) std::cout << "Case #" << kase << ": ", mian();
	return 0;
}