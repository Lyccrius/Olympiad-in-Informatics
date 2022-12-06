#include <cstdio>

const int maxM = 20 + 10;
const int maxN = 20 + 10;

int M, N, X, Y;
int map[maxM][maxN];
int vis[maxM][maxN];
int c;
int turnX[5] = {0, 1, 0, -1};
int turnY[5] = {1, 0, -1, 0};
int extX[5] = {1, 1, -1, -1};
int extY[5] = {1, -1, 1, -1};

void DFS(int x, int y) {
	if (x < 0 || x > M + 1) return;
	if (y < 0 || y > N + 1) return;
	if (!map[x][y]) return;
	if (vis[x][y]) return;
	vis[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int xx = x + turnX[i];
		int yy = y + turnY[i];
		if (map[xx][yy]) DFS(xx, yy);
		else c++;
	}
	for (int i = 0; i < 4; i++) {
		int xx = x + extX[i];
		int yy = y + extY[i];
		if (map[xx][yy]) DFS(xx, yy);
	}
	return;
}

int main() {
	scanf("%d%d%d%d", &M, &N, &X, &Y);
	for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) {
		char ch;
		scanf(" %c", &ch);
		if (ch == 'X') map[i][j] = true;
	}
	DFS(X, Y);
	printf("%d\n", c);
	return 0;
}