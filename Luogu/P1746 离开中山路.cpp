#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int inf = 1e9 + 10;
const int maxN = 1000 + 10;

typedef std::pair<int, int> pii;

int n;
int x1, y1, x2, y2;
int map[maxN][maxN];
int dis[maxN][maxN];
int vis[maxN][maxN];

int deltaX[5] = {0, -1, 0, 1};
int deltaY[5] = {-1, 0, 1, 0};

void BFS(int x, int y) {
    std::queue<pii> waiting;
    waiting.push(std::make_pair(x, y));
    while (!waiting.empty()) {
        int xx = waiting.front().first;
        int yy = waiting.front().second;
        waiting.pop();
        if (vis[xx][yy]) continue;
        vis[xx][yy] = true;
        for (int i = 0; i < 4; i++) {
            int xxx = xx + deltaX[i];
            int yyy = yy + deltaY[i];
            if (map[xxx][yyy]) continue;
            if (xxx > 0 && xxx <= n)
            if (yyy > 0 && yyy <= n) {
                dis[xxx][yyy] = std::min(dis[xxx][yyy], dis[xx][yy] + 1);
                waiting.push(std::make_pair(xxx, yyy));
            }
        }
    }
    return;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ch;
            scanf(" %c", &ch);
            map[i][j] = ch - '0';
        }
    }
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    std::memset(dis, inf, sizeof(dis));
    dis[x1][y1] = 0;
    BFS(x1, y1);
    printf("%d\n", dis[x2][y2]);
    return 0;
}