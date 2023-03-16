#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 100;
const int maxM = 20;
const lxl inf = 2e18 + 10;

int n, m, b;
int x, k, q;
int t;

struct Node {
    int x, k;
    int other;

    bool operator<(const Node &other) const {
        return k < other.k;
    }
} node[maxN + 10];

lxl f[2][(1 << maxM) + 10];

bool check(int all, int part) {
    return (all & part) ^ part;
}

lxl ans = inf;

int main() {
    std::cin >> n >> m >> b;
    for (int i = 1; i <= n; i++) {
        std::cin >> x >> k >> q;
        node[i].x = x;
        node[i].k = k;
        for (int j = 1; j <= q; j++) {
            std::cin >> t;
            node[i].other |= (1 << (t - 1));
        }
    }
    std::sort(node + 1, node + n + 1);
    std::fill(f[0], f[0] + 2 * (1 << m), inf);
    f[0][0] = 0;
    for (int i = 0; i < n; i++) {
        //std::fill(f[(i + 1) & 1], f[(i + 1) & 1] + (1 << m), inf);
        for (int j = 0; j < (1 << m); j++) f[(i + 1) & 1][j] = inf;
        for (int j = 0; j < (1 << m); j++) {
            f[(i + 1) & 1][j] = std::min(f[(i + 1) & 1][j], f[i & 1][j]);
            //if (check(j, node[i].other)) continue;
            f[(i + 1) & 1][j | node[i + 1].other] = std::min(f[(i + 1) & 1][j | node[i + 1].other], f[i & 1][j] + node[i + 1].x);
        }
        //for (int j = 0; j < (1 << m); j++) printf("f[%d][%d] = %d\n", i, j, f[(i + 1) & 1][j]);
        ans = std::min(ans, f[(i + 1) & 1][(1 << m) - 1] + 1ll * node[i + 1].k * b);
    }
    for (int i = 1; i <= n; i++) 
    if (ans == inf) ans = - 1;
    std::cout << ans;
    return 0;
}