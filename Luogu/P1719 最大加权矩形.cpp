#include <cstdio>
#include <algorithm>

const int maxn = 120 + 10;
const int inf = 0x3f3f3f3f;

int n;

int matrix[maxn][maxn];
int pre[maxn][maxn];
int ans = -inf;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &matrix[i][j]);
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + matrix[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = i; k <= n; k++) {
				for (int l = j; l <= n; l++) {
					ans = std::max(ans, pre[k][l] - pre[i - 1][l] - pre[k][j - 1] + pre[i - 1][j - 1]);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}