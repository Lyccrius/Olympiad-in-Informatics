#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int inf = 0x3f3f3f3f;
const int maxX = 20 + 10;
const int maxY = 20 + 10;

typedef std::pair<int, int> pii;
typedef std::pair<pii, int> ppi;

int deltaX[20] = {-2, -1, 1, 2, 2,  2,  2,  1, -1, -2, 2, -2};
int deltaY[20] = { 2,  2, 2, 2, 1, -1, -2, -2, -2, -2, 1, -1};

int x1, y1;
int x2, y2;
int dis[maxX][maxY];
int vis[maxX][maxY];

int BFS(int x, int y) {
    std::queue<ppi> waiting;
    waiting.push(std::make_pair(std::make_pair(1, 1), 0));
    while (!waiting.empty()) {
        int xx = waiting.front().first.first;
        int yy = waiting.front().first.second;
        int dd = waiting.front().second;
        waiting.pop();
        if (vis[xx][yy]) continue;
        vis[xx][yy] = true;
        dis[xx][yy] = dd;
        if (xx == x && yy == y) break;
        for (int i = 0; i < 12; i++) {
            int xxx = xx + deltaX[i];
            int yyy = yy + deltaY[i];
            if (xxx >= 1 && xxx < maxX)
            if (yyy >= 1 && yyy < maxY) {
                waiting.push(std::make_pair(std::make_pair(xxx, yyy), dis[xx][yy] + 1));
            }
        }
    }
    return dis[x][y];
}

int main() {
    dis[1][1] = 0;
    scanf("%d%d", &x1, &y1);
    scanf("%d%d", &x2, &y2);
    printf("%d\n", BFS(x1, y1));
    std::memset(dis, 0, sizeof(dis));
    std::memset(vis, 0, sizeof(vis));
    printf("%d\n", BFS(x2, y2));
    return 0;
}