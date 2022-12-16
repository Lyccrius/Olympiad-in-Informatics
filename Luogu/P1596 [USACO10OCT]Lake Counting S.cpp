#include <cstdio>

const int maxN = 100 + 10;
const int maxM = 100 + 10;

const int dx[10] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
const int dy[10] = {0, -1, 0, 1, -1, 1, -1, 0, 1};

int N, M;
char map[maxN][maxM];
bool vis[maxN][maxM];
int cnt;

void DFS(int x,int y) {
	if (x < 1 || x > N) return;
	if (y < 1 || y > M) return;
	if (map[x][y] == '.') return;
	if (vis[x][y]) return;
    vis[x][y] = true;
    for (int i = 1; i <= 8; i++) DFS(x + dx[i], y + dy[i]);
	return;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) scanf(" %c", &map[i][j]);
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) if (map[i][j] == 'W' && !vis[i][j]) cnt++, DFS(i, j);
    printf("%d\n", cnt);
    return 0;
}