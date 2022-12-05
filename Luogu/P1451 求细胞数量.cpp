#include <cstdio>

const int maxN = 100 + 10;
const int maxM = 100 + 10;

int n, m;
int map[maxN][maxM];
int vis[maxN][maxM];
int cnt;

void DFS(int x, int y) {
	if (x < 1 || x > n) return;
	if (y < 1 || y > m) return;
	if (!map[x][y] || vis[x][y]) return;
	vis[x][y] = true;
	DFS(x - 1, y);
	DFS(x + 1, y);
	DFS(x, y - 1);
	DFS(x, y + 1);
	return;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%1d", &map[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (map[i][j] && !vis[i][j]) DFS(i, j), cnt++;
	printf("%d\n", cnt);
	return 0;
}