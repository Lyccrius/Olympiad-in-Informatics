#include <iostream>
#include <queue>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}


typedef long long lxl;
typedef std::pair<int, int> pii;

const lxl inf = 1e18;
const int dx[5] = {0, 0, 1, 0, -1};
const int dy[5] = {0, 1, 0, -1, 0};

const int maxN = 1000;
const int maxM = 1000;

int n, m, a, b, c;
lxl R[maxN + 10][maxM + 10];
lxl D[5][maxN + 10][maxM + 10];
int V[5][maxN + 10][maxM + 10];
lxl ans = inf;

struct Node {
    int x, y;
    lxl dis;
    bool operator<(const Node &other) const {
        return dis > other.dis;
    }
};

void BFS(int cur, int x, int y) {
    D[cur][x][y] = R[x][y];
    std::priority_queue<Node> q;
    q.push((Node) {x, y, D[cur][x][y]});
    while (q.size()) {
        x = q.top().x;
        y = q.top().y;
        q.pop();
        if (V[cur][x][y]) continue;
        V[cur][x][y] = true;
        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || yy > m) continue;
            if (D[cur][xx][yy] > D[cur][x][y] + R[xx][yy]) {
                D[cur][xx][yy] = D[cur][x][y] + R[xx][yy];
                q.push((Node) {xx, yy, D[cur][xx][yy]});
            }
        }
    }
    return;
}

int main() {
    std::cin >> n >> m >> a >> b >> c;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> R[i][j];
    std::memset(D, 0x3f, sizeof(D));
    BFS(1, 1, a);
    BFS(2, n, b);
    BFS(3, n, c);
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << D[1][i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << D[2][i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cout << D[3][i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    */
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans = std::min(ans, D[1][i][j] + D[2][i][j] + D[3][i][j] - R[i][j] - R[i][j]);
    std::cout << ans << '\n';
    return 0;
}