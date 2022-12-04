#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int inf = 1e9 + 10;
const int mod = 1e9 + 7;

int n;
int a[maxN];
int gcd = inf;
long long res = 1;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), gcd = std::min(gcd, a[i]);
	for (int i = 1; i <= n; i++) res = (res * (a[i] / gcd)) % mod;
	printf("%d %lld\n", gcd, res);
	return 0;
}