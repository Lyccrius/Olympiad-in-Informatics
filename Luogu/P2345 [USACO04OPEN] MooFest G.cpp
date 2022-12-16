#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 1e5 + 10;

int n, m;
int v[maxN];
int x[maxN];
long long ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &v[i], &x[i]);
	for (int i = 1; i <= n; i++) for (int j = i + 1;j <= n; j++) ans += std::max(v[i], v[j]) * std::abs(x[i] - x[j]);
	printf("%lld\n", ans);
	return 0;
}