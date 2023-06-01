#include <iostream>

typedef long long lxl;

const int maxN = 100;

int t;
int n;
lxl a[maxN + 10];
lxl ans;

lxl SG(lxl x) {
	if (x & 1) return SG(x / 2);
	else return x / 2;
}

void mian() {
	ans = 0;
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		ans ^= SG(a[i]);
	}
	if (ans) std::cout << "YES" << '\n';
	else std::cout << "NO" << '\n';
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}