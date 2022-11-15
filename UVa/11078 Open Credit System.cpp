#include <cstdio>
#include <algorithm>

const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 10;

int T;
int n;
int a[maxn];

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d", &n);
		int ans = -inf;
		int maxA = -inf;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			ans = std::max(ans, maxA - a[i]);
			maxA = std::max(maxA, a[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}