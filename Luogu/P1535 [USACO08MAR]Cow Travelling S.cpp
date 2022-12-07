#include <cstdio>
#include <cmath>

const int maxN = 100 + 10;
const int maxM = 100 + 10;
const int maxT = 15+ 10;

int N, M, T;
char map[maxN][maxM];
int res[maxN][maxM][maxT];
int R1, C1, R2, C2;

int Dis(int x, int y) {
    x = std::abs(x - R2);
    y = std::abs(y - C2);
    return x + y;
}

int DFS(int x, int y, int t) {
    if (t > T) return res[x][y][t] = 0;
    if (res[x][y][t]) return res[x][y][t];
    if (map[x][y] == '*') return res[x][y][t] = 0;
    if (Dis(x, y) > T - t) return res[x][y][t] = 0;
    if (x < 1 || x > N || y < 1 || y > M) return res[x][y][t] = 0;
    if (t == T && x == R2 && y == C2) return res[x][y][t] = 1;
    if (t == T) return res[x][y][t] = 0;
    int ans = 0;
    ans += DFS(x - 1, y, t + 1);
    ans += DFS(x + 1, y, t + 1);
    ans += DFS(x, y - 1, t + 1);
    ans += DFS(x, y + 1, t + 1);
    return res[x][y][t] = ans;
}

int main() {
    scanf("%d%d%d", &N, &M, &T);
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) scanf(" %c", &map[i][j]);
    scanf("%d%d%d%d", &R1, &C1, &R2, &C2);
    int ans = DFS(R1, C1, 0);
    printf("%d\n", ans);
    return 0;
}