#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

typedef std::pair<int, int> pii;

const int maxX = 100;
const int maxY = 100;
const int dx[10] = {0, -1, -1, -1, 1, 1, 1, 0, 0};
const int dy[10] = {0, -1, 0, 1, -1, 0, 1, -1, 1};

int X, Y, Mx, My;
char map[maxX + 10][maxY + 10];
bool vis[maxX + 10][maxY + 10];
int dis[maxX + 10][maxY + 10];
int ans;

void BFS() {
    std::queue<pii> q;
    q.push(std::make_pair(Mx, My));
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (vis[x][y]) continue;
        vis[x][y] = true;
        ans = std::max(ans, dis[x][y]);
        //printf("BFS(%d, %d), %d\n", x, y, dis[x][y]);
        for (int i = 1; i <= 8; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            //printf("xx = %d, yy = %d\n", xx, yy);
            if (xx < 1 || xx > X) continue;
            if (yy < 1 || yy > Y) continue;
            if (map[yy][xx] == '*') continue;
            if (dis[xx][yy]) continue;
            dis[xx][yy] = dis[x][y] + 1;
            q.push(std::make_pair(xx, yy));
        }
    }
    return;
}

int main() {
    std::cin >> X >> Y >> Mx >> My;
    for (int i = Y; i >= 1; i--) {
        for (int j = 1; j <= X; j++) {
            std::cin >> map[i][j];
        }
    }
    //std::memset(dis, 0x3f, sizeof(dis));
    dis[Mx][My] = 0;
    BFS();
    std::cout << ans;
    return 0;
}