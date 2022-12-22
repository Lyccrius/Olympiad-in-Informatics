#include <cstdio>

const int maxN = 211985 + 10;
const int maxA = 233333 + 10;
const int mod = 1e9 + 7;

int n;
int a[maxN];
int f[maxA];
int ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = (a[i] - 1) & a[i]; j; j = (j - 1) & a[i]) f[j] = (f[j] + f[a[i]] + 1) % mod;
		ans = (ans + f[a[i]]) % mod;
	}
	printf("%d\n", ans);
	return 0;
}