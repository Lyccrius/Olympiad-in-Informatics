#include <iostream>
#include <deque>

typedef char chr;

const int maxN = 1000;
const int maxM = 1000;
const int dx[5] = {0, 0, 1, 0, -1};
const int dy[5] = {0, 1, 0, -1, 0};

int n, m;
chr a[maxN + 10][maxM + 10];
int d[maxN + 10][maxM + 10][5];

struct Node {
    int x, y;
    int dir;
    int dis;
};

void BFS() {
    std::deque<Node> q;
    q.push_back((Node) {1, 1, 1, 0});
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int dir = q.front().dir;
        int dis = q.front().dis;
        q.pop_front();
        if (d[x][y][dir]) continue;
        d[x][y][dir] = dis;
        //printf("%d, %d, %d, %d\n", x, y, dir, dis);
        if (x == n && y == m + 1) {
            std::cout << dis << '\n';
            return;
        }
        for (int i = 1; i <= 4; i++) {
            if (i != dir && a[x][y] != '#') continue;
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 1 || xx > n) continue;
            if (yy < 1 || (yy > m && xx != n)) continue;
            if (i == dir) q.push_front((Node) {xx, yy, i, dis});
            else q.push_back((Node) {xx, yy, i, dis + 1});
        }
    }
    std::cout << -1 << '\n';
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    BFS();
    return 0;
}