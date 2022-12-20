#include <cstdio>

long long x, y;
long long ans;

int main() {
	scanf("%lld%lld", &x, &y);
	while (x) {
		ans += 4 * x * (y / x);
		long long t = x;
		x = y % x;
		y = t;
	}
	printf("%lld\n", ans);
    return 0;
}