#include <cstdio>
#include <algorithm>

const int maxN = 5e6 + 10;
const int inf = 1e9 + 10;

int n, p;
int a[maxN];
int x, y, z;

int dif[maxN];
int pre;
int ans = inf;

int main() {
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), dif[i] = a[i] - a[i - 1];
	for (int i = 1; i <= p; i++) scanf("%d%d%d", &x, &y, &z), dif[x] += z, dif[y + 1] -= z;
	for (int i = 1; i <= n; i++) pre += dif[i], ans = std::min(ans, pre);
	printf("%d\n", ans);
	return 0;
}