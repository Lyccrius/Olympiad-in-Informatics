#include <iostream>
#include <algorithm>
#include <deque>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef char chr;

const int maxN = 200;
const int maxM = 200;
const int maxK = 200;
const int maxT = 40000;

const int inf = 1e9 + 10;
const int dx[5] = {0, - 1, 1, 0, 0};
const int dy[5] = {0, 0, 0, - 1, 1};

int N, M, x, y, K;
chr a[maxN + 10][maxM + 10];
int f[maxN + 10][maxM + 10];
int s, t, d;
int g;
int ans;

struct Node {
    int val;
    int dis;
};

void solve(int x, int y, int g, int d) {
    std::deque<Node> q;
    for (int i = 1; 1 <= x && x <= N && 1 <= y && y <= M; i++, x += dx[d], y += dy[d]) {
        if (a[x][y] == 'x') {
            q.clear();
            continue;
        }
        while (q.size() && q.back().val + i - q.back().dis < f[x][y]) q.pop_back();
        q.push_back((Node) {f[x][y], i});
        if (q.back().dis - q.front().dis > g) q.pop_front();
        f[x][y] = q.front().val + i - q.front().dis;
        ans = std::max(ans, f[x][y]);
    }
    return;
}

int main() {
    promote();
    std::cin >> N >> M >> x >> y >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            std::cin >> a[i][j];
        }
    }
    std::fill(f[0], f[0] + (maxN + 10) * (maxM + 10), - inf);
    f[x][y] = 0;
    for (int i = 1; i <= K; i++) {
        std::cin >> s >> t >> d;
        g = t - s + 1;
        if (d == 1) for (int j = 1; j <= M; j++) solve(N, j, g, d);
        if (d == 2) for (int j = 1; j <= M; j++) solve(1, j, g, d);
        if (d == 3) for (int j = 1; j <= N; j++) solve(j, M, g, d);
        if (d == 4) for (int j = 1; j <= N; j++) solve(j, 1, g, d);
    }
    std::cout << ans << '\n';
    return 0;
}