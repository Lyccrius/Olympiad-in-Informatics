#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 5000 + 10;

int n, m;

struct Player {
    int k;
    int s;

    bool operator<(Player other) const {
        if (s != other.s) return s > other.s;
        return k < other.k;
    }
};

Player player[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d%d", &player[i].k, &player[i].s);
    std::sort(player + 1, player + 1 + n);
    m = std::floor(m * 1.5);
    while (player[m].s == player[m + 1].s) m++;
    printf("%d %d\n", player[m].s, m);
    for (int i = 1; i <= m; i++) printf("%d %d\n", player[i].k, player[i].s);
    return 0;
}