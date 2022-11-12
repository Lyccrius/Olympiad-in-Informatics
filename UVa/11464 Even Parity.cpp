#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 15 + 10;
const int inf = 0x3f3f3f3f;

int T;

int n;
int originGrid[maxn][maxn];
int grid[maxn][maxn];

int check(int line) {
    std::memset(grid, 0, sizeof(grid));
    for (int i = 1; i <= n; i++) {
        if (line >> (i - 1) & 1) grid[1][i] = 1;
        else if (originGrid[1][i]) return inf;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = 0;
            if (i > 2) sum += grid[i - 2][j];
            if (j > 1) sum += grid[i - 1][j - 1];
            if (j < n) sum += grid[i - 1][j + 1];
            grid[i][j] = sum % 2;
            if (originGrid[i][j] && !grid[i][j]) return inf;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (originGrid[i][j] != grid[i][j]) cnt++;
    return cnt;
}

int main() {
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &originGrid[i][j]);
        int maxOpt = 1 << n;
        int ans = inf;
        for (int opt = 0; opt < maxOpt; opt++) ans = std::min(ans, check(opt));
        if (ans == inf) ans = -1;
        printf("Case %d: %d\n", kase, ans);
    }
    return 0;
}