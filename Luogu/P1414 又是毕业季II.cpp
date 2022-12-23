#include <cstdio>
#include <algorithm>

const int maxN = 1e4 + 10;
const int inf = 1e6 + 10;

int n;
int a[maxN];
int c[inf];
int f[maxN];
int m;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= a[i]; j++) {
			if (a[i] % j == 0) {
				c[j]++;
				if (j != a[i] / j) c[a[i] / j]++;
			}
		}
	}
	m = 1e6;
	for (int i = 1; i <= m; i++) f[c[i]] = i;
	for (int i = n; i >= 1; i--) f[i] = std::max(f[i], f[i + 1]);
	for (int i = 1; i <= n; i++) printf("%d\n", f[i]);
	return 0;
}