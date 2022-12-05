#include <cstdio>

const int maxN = 30 + 10;

int n;
int map[maxN][maxN];
int vis[maxN][maxN];

void DFS(int x, int y) {
	if (x < 0 || x > n + 1 || y < 0 || y > n + 1) return;
	if (vis[x][y]) return;
	vis[x][y] = true;
	if (map[x][y]) return;
	DFS(x - 1, y);
	DFS(x + 1, y);
	DFS(x, y - 1);
	DFS(x, y + 1);
	return;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &map[i][j]), vis[i][j] = map[i][j];
	DFS(0, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) if (vis[i][j]) printf("%d ", map[i][j]); else printf("%d ", 2);
		printf("\n");
	}
	return 0;
}