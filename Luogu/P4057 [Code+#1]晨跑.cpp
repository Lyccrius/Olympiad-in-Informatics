#include <cstdio>
#include <algorithm>

long long a, b, c;
long long ans;

long long gcd(long long x,long long y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

long long lcm(long long x, long long y) {
	return x * y / gcd(x, y);
}

int main() {
	scanf("%lld%lld%lld", &a, &b, &c);
	ans = lcm(lcm(a, b), c);
	printf("%lld\n", ans);
	return 0;
}