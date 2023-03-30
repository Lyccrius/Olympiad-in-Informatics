#include <iostream>

typedef unsigned long long lxl;

const int maxN = 2e5;

int t;
int n;
lxl a[maxN + 10];
lxl b[maxN + 10];

lxl gcd(lxl x, lxl y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

lxl lcm(lxl x, lxl y) {
	return x / gcd(x, y) * y;
}

void mian() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
	for (int i = 1; i <= n; i++) a[i] *= b[i];
	int ans = 0;
    //printf("a[1] = %lld\n", a[1]);
	lxl g = 1;
	lxl l = 2;
	for (int i = 1; i <= n; i++) {
		//c[i] = gcd(c[i - 1], a[i]);
		g = gcd(g, a[i]);
		l = lcm(l, b[i]);
		if (g % l) {
			g = a[i];
			l = b[i];
			ans++;
		}
        //printf("a[%d] = %lld, p[%d] = %d, c[%d] = %lld", i, a[i], i, p[i], i, c[i]);
        //printf(", ans = %lld\n", ans);
	}
	std::cout << ans << '\n';
	return;
}

int main() {
	std::cin >> t;
	while (t--) mian();
	return 0;
}