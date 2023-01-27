#include <iostream>
#include <algorithm>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int inf = 1e9;

const int maxN = 12;
const int maxM = 1e3;
const int maxW = 5e5;

int n, m;
int u, v, w;

int a[maxN + 10][maxN + 10];
lxl f[maxN + 10][(1 << maxN) + 10];
lxl d[(1 << maxN) + 10][(1 << maxN) + 10];
int log[(1 << maxN) + 10];
lxl ans;

int lowbit(int x) {
    return x & -x;
}

int main() {
    ans = inf;
    std::fill(a[0], a[0] + (maxN + 10) * (maxN + 10), inf);
    std::fill(f[0], f[0] + (maxN + 10) * (1 << maxN), inf);
    //std::memset(a, 0x3f, sizeof(a));
    //std::memset(f, 0x3f, sizeof(f));
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        a[u][v] = std::min(a[u][v], w);
        a[v][u] = std::min(a[v][u], w);
    }
    for (int i = 0; i <= n; i++) log[1 << i] = i;
    for (int i = 0; i <= n; i++) f[0][1 << i] = 0;
    for (int i = 1; i < (1 << n); i++) {
        int c = ((1 << n) - 1) ^ i;
        int next[(1 << n) + 10];
        int last = 0;
        for (int j = c; j; j = (j - 1) & c) next[j] = last, last = j;
        for (int j = last; j; j = next[j]) {
            int now = log[lowbit(j)] + 1;
            int t = inf;
            for (int k = 1; k <= n; k++) {
                if (1 << (k - 1) & i) {
                    t = std::min(t, a[now][k]);
                }
            }
            d[i][j] = d[i][j ^ lowbit(j)] + t;
            //printf("d[%d][%d] = %d, ", i, j, d[i][j]);
        }
        //printf("\n");
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < (1 << n); j++) {
            for (int k = j; k; k = (k - 1) & j) {
                f[i][j] = std::min(f[i][j], f[i - 1][j ^ k] + i * d[j ^ k][k]);
            }
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < (1 << n); j++) {
            //printf("f[%d][%d] = %d, ", i, j, f[i][j]);
        }
        //printf("\n");
    }
    for (int i = 0; i <= n; i++) ans = std::min(ans, f[i][(1 << n) - 1]);
    std::cout << ans << '\n';
    return 0;
}