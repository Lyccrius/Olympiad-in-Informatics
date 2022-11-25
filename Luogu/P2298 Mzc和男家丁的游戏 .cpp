#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int inf = 1e9 + 10;
const int maxN = 2000 + 10;
const int maxM = 2000 + 10;

typedef std::pair<int, int> pii;

int deltaX[5] = {0, -1, 0, 1};
int deltaY[5] = {-1, 0, 1, 0};

int n, m;
int map[maxN][maxM];
int dis[maxN][maxM];
int vis[maxN][maxM];
int mX, mY;
int dX, dY;

void BFS(int x, int y) {
    std::queue<pii> waiting;
    waiting.push(std::make_pair(x, y));
    while (!waiting.empty()) {
        int xx = waiting.front().first;
        int yy = waiting.front().second;
        waiting.pop();
        if (vis[xx][yy]) continue;
        vis[xx][yy] = true;
        if (xx == dX && yy == dY) return;
        for (int i = 0; i < 4; i++) {
            int xxx = xx + deltaX[i];
            int yyy = yy + deltaY[i];
            if (xxx > 0 && xxx <= n)
            if (yyy > 0 && yyy <= m) 
            if (map[xxx][yyy]) {
                dis[xxx][yyy] = std::min(dis[xxx][yyy], dis[xx][yy] + 1);
                waiting.push(std::make_pair(xxx, yyy));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    std::memset(dis, inf, sizeof(dis));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            scanf(" %c", &ch);
            switch (ch) {
                case 'm': {
                    mX = i;
                    mY = j;
                    map[i][j] = true;
                    break;
                }
                case 'd': {
                    dX = i;
                    dY = j;
                    map[i][j] = 2;
                    break;
                }
                case '.': {
                    map[i][j] = true;
                    break;
                }
                case '#': {
                    map[i][j] = false;
                    break;
                }
            }
        }
    }
    dis[mX][mY] = 0;
    BFS(mX, mY);
    if (vis[dX][dY]) printf("%d\n", dis[dX][dY]);
    else printf("No Way!\n");
    return 0;
}