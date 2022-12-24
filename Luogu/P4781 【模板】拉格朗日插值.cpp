#include <cstdio>

const int maxN = 2e3 + 10;
const int mod = 998244353;

int n, k;
int x[maxN], y[maxN];

long long pow(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}

long long inv(int a) {
	return pow(a, mod - 2);
}

long long f(int k) {
	long long ret = 0;
	for (int i = 1; i <= n; i++) {
		long long t = y[i] % mod;
		for (int j = 1; j <= n; j++) if (j != i) t = t * (k - x[j]) % mod * inv(x[i] - x[j]) % mod;
		ret = (ret + t) % mod;
	}
	return ret;
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	printf("%lld\n", (f(k) + mod) % mod);
	return 0;
}