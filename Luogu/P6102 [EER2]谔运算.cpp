#include <cstdio>

const int maxN = 5e5 + 10;

unsigned n;
unsigned a[maxN];
unsigned t[50];
unsigned tot;
unsigned ans = 0;

int main() {
	scanf("%u", &n);
	tot = n * n;
	for (int i = 1; i <= n; i++) scanf("%u", &a[i]);
	for (int i = 1; i <= n; i++) for (int j = 0; j < 32; j++) if ((a[i] >> j) & 1) t[j]++;
	for (int i = 0; i < 32; i++) {
		unsigned resA = t[i] * t[i];
		unsigned resO = (n - t[i]) * (n - t[i]);
		ans += (resA * resO + (tot - resA) * (tot - resO)) << i;
	}
	printf("%u\n", ans);
	return 0;
}