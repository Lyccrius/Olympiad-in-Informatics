#include <cstdio>

const int maxN = 1e3 + 10;
const int maxM = 1e3 + 10;
const int maxK = 1e3 + 10;

int n, m, k;
int a[maxN][maxM];
int ans[maxK];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			ans[a[i][j]] += j;
		}
	}
	for (int i = 1; i <= k; i++) printf("%d ", ans[i]);
	return 0;
}