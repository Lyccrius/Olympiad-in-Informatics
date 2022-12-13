#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int maxW = 1000 + 10;
const int maxH = 1000 + 10;
const int inf = 1e9 + 10;

int dx[5] = {0, 1, 0, -1};
int dy[5] = {1, 0, -1, 0};

int W, H;
int map[maxW][maxH];
int x1, y1;
int x2, y2;
int vis1[maxW][maxH];
int vis2[maxW][maxH];
int dis1[maxW][maxH];
int dis2[maxW][maxH];
int ans;

void BFS() {
	std::memset(dis1, inf, sizeof(dis1));
	std::memset(dis2, inf, sizeof(dis2));
	std::queue<std::pair<int, int> > q1;
	std::queue<std::pair<int, int> > q2;
	vis1[x1][y1] = true;
	vis2[x2][y2] = true;
	dis1[x1][y1] = 0;
	dis2[x2][y2] = 0;
	q1.push(std::make_pair(x1, y1));
	q2.push(std::make_pair(x2, y2));
	while (!q1.empty()) {
		int x = q1.front().first;
		int y = q1.front().second;
		q1.pop();
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i];
			int yy = y + dy[i];
			if (vis1[xx][yy]) continue;
			if (xx < 1 || xx > W) continue;
			if (yy < 1 || yy > H) continue;
			if (map[xx][yy] == 1) continue;
			if (dis1[x][y] + 1 >= dis1[xx][yy]) continue;
			vis1[xx][yy] = true;
			dis1[xx][yy] = dis1[x][y] + 1;
			q1.push(std::make_pair(xx, yy));
		}
	}
	while (!q2.empty()) {
		int x = q2.front().first;
		int y = q2.front().second;
		q2.pop();
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i];
			int yy = y + dy[i];
			if (vis2[xx][yy]) continue;
			if (xx < 1 || xx > W) continue;
			if (yy < 1 || yy > H) continue;
			if (map[xx][yy] == 1) continue;
			if (dis2[x][y] + 1 >= dis2[xx][yy]) continue;
			vis2[xx][yy] = true;
			dis2[xx][yy] = dis2[x][y] + 1;
			q2.push(std::make_pair(xx, yy));
		}
	}
	return;
}

int main() {
	scanf("%d%d", &H, &W);
	for (int i = 1; i <= W; i++) for (int j = 1; j <= H; j++) {
		scanf("%d", &map[i][j]);
		if (map[i][j] == 2) x1 = i, y1 = j;
		if (map[i][j] == 3) x2 = i, y2 = j;
	}
	BFS();
	ans = inf;
	for (int i = 1; i <= W; i++) for (int j = 1; j <= H; j++) if (map[i][j] == 4) ans = std::min(ans, dis1[i][j] + dis2[i][j]);
	printf("%d\n", ans);
	return 0;
}