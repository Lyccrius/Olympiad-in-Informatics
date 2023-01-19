#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::pair<int, int> pii;

const int maxN = 500;
const int maxM = 500;
const int dx[5] = {0, 1, 0, -1, 0};
const int dy[5] = {0, 0, -1, 0, 1};

int n, m, k;
char map[maxN + 10][maxM + 10];
bool vis[maxN + 10][maxM + 10];
std::vector<pii> v;
int sx, sy;

void DFS(int x, int y) {
    v.push_back(std::make_pair(x, y));
    vis[x][y] = true;
    for (int i = 1; i <= 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 1 || xx > n) continue;
        if (yy < 1 || yy > m) continue;
        if (map[xx][yy] == '#') continue;
        if (vis[xx][yy]) continue;
        DFS(xx, yy);
    }
    return;
}

int main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> map[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (map[i][j] == '.') {
        sx = i;
        sy = j;
        break;
    }
    DFS(sx, sy);
    for (int i = 1; i <= k; i++) map[v.back().first][v.back().second] = 'X', v.pop_back();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) std::cout << map[i][j];
        std::cout << '\n';
    }
    return 0;
}