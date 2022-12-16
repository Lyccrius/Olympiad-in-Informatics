#include <cstdio>

const int maxN = 5 + 10;
const int maxM = 5 + 10;

const int dx[5] = {0, 1, 0, -1};
const int dy[5] = {1, 0, -1, 0};

int N, M, T;
int SX, SY, FX, FY;
int TX, TY;

bool map[maxN][maxM];
bool vis[maxN][maxM];
int cnt;

void DFS(int x, int y) {
	if (x < 1 || x > N) return;
	if (y < 1 || y > M) return;
	if (map[x][y]) return;
	if (vis[x][y]) return;
	vis[x][y] = true;
	if (x == FX && y == FY) cnt++;
	for (int i = 0; i < 4; i++) DFS(x + dx[i], y + dy[i]);
	vis[x][y] = false;
	return;
}

int main() {
	scanf("%d%d%d", &N, &M, &T);
	scanf("%d%d%d%d", &SX, &SY, &FX, &FY);
	while (T--) scanf("%d%d", &TX, &TY), map[TX][TY] = true;
	DFS(SX, SY);
	printf("%d\n", cnt);
	return 0;
}