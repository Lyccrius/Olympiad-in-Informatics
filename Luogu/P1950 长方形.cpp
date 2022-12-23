#include <cstdio>
#include <algorithm>

const int maxN = 1000 + 10;
const int maxM = 1000 + 10;
const int inf = 1e9 + 10;

int n, m;
char map[maxN][maxM];
int h[maxN][maxM];
long long cnt;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf(" %c", &map[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (map[i][j] == '.') h[i][j] = h[i - 1][j] + 1;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (map[i][j] == '.') {
		int x = inf;
		for (int k = j; k >= 1 && map[i][k] == '.' && x; k--) {
			x = std::min(x, h[i][k]);
			cnt += x;
		}
	}
	printf("%lld\n", cnt);
	return 0;
}