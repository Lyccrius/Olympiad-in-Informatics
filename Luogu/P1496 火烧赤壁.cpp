#include <cstdio>
#include <algorithm>

const int maxN = 2e4 + 10;

int n;
int a[maxN];
int b[maxN];

int raw[maxN << 1];
int m;

int vis[maxN << 1];
int ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]), raw[++m] = a[i], raw[++m] = b[i];
	std::sort(raw + 1, raw + m + 1);
	m = std::unique(raw + 1, raw + m + 1) - raw - 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(raw + 1, raw + m + 1, a[i]) - raw, b[i] = std::lower_bound(raw + 1, raw + m + 1, b[i]) - raw;
	for (int i = 1; i <= n; i++) for (int j = a[i]; j < b[i]; j++) vis[j]++;
	for (int i = 1; i <= m; i++) if (vis[i]) ans += raw[i + 1] - raw[i];
	printf("%d\n", ans);
	return 0;
}