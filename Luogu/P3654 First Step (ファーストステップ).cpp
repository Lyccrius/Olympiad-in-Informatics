#include <cstdio>

const int maxR = 100 + 10;
const int maxC = 100 + 10;

int dx[5] = {0, 1, 0, -1};
int dy[5] = {1, 0, -1, 0};

int R, C, K;
char map[maxR][maxC];
int cnt;

void DFS(int x, int y) {
	for (int i = 0; i < 4; i++) {
		bool ok = true;
		for (int j = 1; j < K; j++) {
			int xx = x + j * dx[i];
			int yy = y + j * dy[i];
			if (xx < 1 || xx > R) {ok = false; break;}
			if (yy < 1 || yy > C) {ok = false; break;}
			if (map[xx][yy] != '.') {ok = false; break;}
		}
		if (ok) cnt++;
	}
	return;
}

int main() {
	scanf("%d%d%d", &R, &C, &K);
	for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) scanf(" %c", &map[i][j]);
	for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) if (map[i][j] == '.') DFS(i, j);
	cnt /= 2;
	if (K == 1) cnt /= 2;
	printf("%d\n", cnt);
	return 0;
}