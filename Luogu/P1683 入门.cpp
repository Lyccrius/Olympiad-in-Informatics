#include <cstdio>

const int maxW = 20 + 10;
const int maxH = 20 + 10;

int W, H;
char map[maxW][maxH];
bool vis[maxW][maxH];
int cnt;

void DFS(int x, int y) {
	if (x < 1 || x > H) return;
	if (y < 1 || y > W) return;
	if (map[x][y] == '#') return;
	if (vis[x][y]) return;
	vis[x][y] = true;
	cnt++;
	DFS(x - 1, y);
	DFS(x + 1, y);
	DFS(x, y - 1);
	DFS(x, y + 1);
	return;
}

int main() {
	scanf("%d%d", &W, &H);
	int x, y;
	for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) {
		scanf(" %c", &map[i][j]);
		if (map[i][j] == '@') {
			x = i;
			y = j;
		}
	}
	DFS(x, y);
	printf("%d\n", cnt);
	return 0;
}