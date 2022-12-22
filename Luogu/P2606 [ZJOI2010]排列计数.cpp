#include <cstdio>

const int maxN = 1e6 + 10;

int n, m;
int p;
long long A[maxN];
long long F[maxN << 1];
int size[maxN << 1];

long long pow(long long a, long long b) {
	long long ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ret;
}

long long C(int n, int m) {
	return A[n] * pow(A[m] * A[n - m] % p, p - 2) % p;
}

long long Lucas(int n, int m) {
	if (m == 0) return 1;
	return Lucas(n / p, m / p) * C(n % p, m % p) % p;
}

int main() {
	scanf("%d%d", &n, &m);
	p = m;
	A[0] = 1;
	for (int i = 1; i <= n; i++) A[i] = A[i - 1] * i % p;
	for (int i = n; i >= 1; i--) size[i] = 1;
	for (int i = n; i >= 2; i--) size[i >> 1] += size[i];
	for (int i = n * 2 + 1; i > n; i--) F[i] = 1;
	for (int i = n; i >= 1; i--) F[i] = Lucas(size[i] - 1, size[i * 2]) * F[i * 2] % p * F[i * 2 + 1] % p;
	printf("%lld\n", F[1]);
	return 0;
}