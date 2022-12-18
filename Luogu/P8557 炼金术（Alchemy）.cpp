#include <cstdio>

const int mod = 998244353;

int n, k;

int pow(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &k);
	printf("%d\n", pow(pow(2, k) - 1, n));
	return 0;
}