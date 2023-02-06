#include <iostream>
#include <cmath>
#include <cstring>

const int maxN = 15;
const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, 1, 0, -1};
const int inf = 1e9;

int n;
double x[maxN + 10];
double y[maxN + 10];

double Dis(int a, int b) {
    double deltaX = x[a] - x[b];
    double deltaY = y[a] - y[b];
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

bool vis[maxN + 10];
double his[maxN + 10];
double dis[maxN + 10][maxN + 10];
double ans;

void DFS(int now, int state, int from, double res) {
    //printf("DFS(%d, %d, %d, %.2lf)\n", now, state, from, res);
    if (now > n) {
        ans = std::min(ans, res);
        return;
    }
    if (res > ans) return;
    for (int next = 1; next <= n; next++) {
        if (vis[next]) continue;
        if (res + dis[from][next] >= ans) continue;
        vis[next] = true;
        state ^= (1 << (next - 1));
        DFS(now + 1, state, next, res + dis[from][next]);
        state ^= (1 << (next - 1));
        vis[next] = false;
    }
    return;
}

int main() {
    ans = inf;
    std::memset(his, 0x3f, sizeof(his));
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) dis[i][j] = dis[j][i] = Dis(i, j);
    DFS(1, 0, 0, 0);
    printf("%.2lf\n", ans);
    return 0;
}