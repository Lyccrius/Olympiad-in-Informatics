#include <cstdio>
#include <iostream>

const int maxN = 1000 + 10;
const int maxM = 1e5 + 10;

int n, m;
bool map[maxN][maxN];
int vis[maxN][maxN];
int bel[maxN][maxN];
int cnt[maxM];

void DFS(int x, int y, int from) {
	if (x < 1 || x > n) return;
	if (y < 1 || y > n) return;
	if (vis[x][y]) return;
	if (bel[x][y]) return;
	vis[x][y] = true;
	bel[x][y] = from;
	cnt[from]++;
	if (map[x][y] ^ map[x - 1][y]) DFS(x - 1, y, from);
	if (map[x][y] ^ map[x + 1][y]) DFS(x + 1, y, from);
	if (map[x][y] ^ map[x][y - 1]) DFS(x, y - 1, from);
	if (map[x][y] ^ map[x][y + 1]) DFS(x, y + 1, from);
	return;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%1d", &map[i][j]);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (!bel[x][y]) DFS(x, y, m);
		printf("%d\n", cnt[bel[x][y]]);
	}
	return 0;
}