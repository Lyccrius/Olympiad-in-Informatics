#include <cstdio>

const int maxP = 1e5 + 10;

int T;
int n, m, p;
long long A[maxP];

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
	if (m > n) return 0;
	return ((A[n] * pow(A[m], p - 2)) % p * pow(A[n - m], p - 2)) % p;
}

long long Lucas(int n, int m) {
	if (m == 0) return 1;
	return (Lucas(n / p, m / p) * C(n % p, m % p)) % p;
}

void mian() {
	scanf("%d%d%d", &n, &m, &p);
	A[0] = 1;
	for (int i = 1; i <= p; i++) A[i] = A[i - 1] * i % p;
	printf("%lld\n", Lucas(n + m, n));
	return;
}

int main() {
	scanf("%d", &T);
	while (T--) mian();
	return 0;
}