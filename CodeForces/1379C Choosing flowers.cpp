#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxT = 1e4;
const int maxN = 1e9;
const int maxM = 1e5;

int t;
int n, m;
int a[maxM + 10], b[maxM + 10];
int v[maxM + 10];

struct Node {
    int val;
    int fir;int ind;

    bool operator<(const Node &other) const {
        return val > other.val;
    }
} node[2 * maxM + 10];

lxl solve(int now, int tot) {
    lxl ret = 0;
    if (tot == 0) return 0;
    if (now > 2 * m) return 0;
    if (node[now].fir == true) {
        if (v[node[now].ind] == false) {
            ret += node[now].val;
        }
        v[node[now].ind] = true;
        ret += solve(now + 1, tot - 1);
    } else {
        if (v[node[now].ind] == false) {
            v[node[now].ind] = true;
            lxl ret1 = a[node[now].ind] + 1ll * (tot - 1) * node[now].val;
            v[node[now].ind] = false;
            lxl ret2 = solve(now + 1, tot);
            ret = std::max(ret1, ret2);
        } else {
            ret = 1ll * tot * node[now].val;
        }
    }
    return ret;
}

void mian() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a[i] >> b[i];
    for (int i = 1; i <= m; i++) v[i] = false;
    for (int i = 1; i <= m; i++) node[i].val = a[i];
    for (int i = 1; i <= m; i++) node[i].fir = true;
    for (int i = 1; i <= m; i++) node[i].ind = i;
    for (int i = 1; i <= m; i++) node[m + i].val = b[i];
    for (int i = 1; i <= m; i++) node[m + i].fir = false;
    for (int i = 1; i <= m; i++) node[m + i].ind = i;
    std::sort(node + 1, node + m + m + 1);
    std::cout << solve(1, n) << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}