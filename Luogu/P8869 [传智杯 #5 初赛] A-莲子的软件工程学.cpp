#include <cstdio>
#include <cmath>

long long sgn(long long b) {
	if (b > 0) return 1;
	else return -1;
}

long long fun(long long a, long long b) {
	return sgn(b) * std::abs(a);
}

int main() {
	long long a, b;
	scanf("%lld%lld", &a, &b);
	printf("%lld\n", fun(a, b));
	return 0;
}