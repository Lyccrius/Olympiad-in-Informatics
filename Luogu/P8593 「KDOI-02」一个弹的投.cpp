#include <iostream>
#include <algorithm>
#include <cmath>

typedef double dbl;
typedef long long lxl;

const int maxN = 5e5;
const dbl g = 9.8;

int n, m;
int x[maxN + 10], y[maxN + 10], v[maxN + 10];
int p[maxN + 10];
int a[maxN + 10];
int b[maxN + 10];

struct Node {
    int i;
    int j;
    int x;
    int y;
    int v;
    dbl e;
} node[maxN + 10];

bool cmpByY(const Node &a, const Node &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

bool cmpByE(const Node &a, const Node &b) {
    return a.e < b.e;
}

bool cmpByB(const int &a, const int &b) {
    return a > b;
}

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} pre, suf;

void solve(int l, int r) {
    dbl t = std::sqrt(2.0 * node[l].y / g);
    for (int i = l; i <= r; i++) node[i].e = 1.0 * node[i].x + t * node[i].v;
    std::sort(node + l, node + r + 1, cmpByE);
    for (int i = l; i <= r; i++) p[node[i].i] += pre.Query(1, 1, n, node[i].j, n), pre.Modify(1, 1, n, node[i].j, 1);
    for (int i = r; i >= l; i--) p[node[i].i] += suf.Query(1, 1, n, 1, node[i].j), suf.Modify(1, 1, n, node[i].j, 1);
    for (int i = l; i <= r; i++) pre.Modify(1, 1, n, node[i].j, - 1);
    for (int i = r; i >= l; i--) suf.Modify(1, 1, n, node[i].j, - 1);
    return;
}

lxl ans;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> x[i] >> y[i] >> v[i];
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) node[i] = (Node) {i, 0, x[i], y[i], v[i]};
    std::sort(node + 1, node + n + 1, cmpByY);
    for (int i = 1; i <= n; i++) node[i].j = i; int l = 1;
    for (int i = 1; i <= n; i++) if (node[i].y != node[i + 1].y) solve(l, i), l = i + 1;
    for (int i = 1; i <= n; i++) b[i] = std::min(p[i], a[i]);
    std::sort(b + 1, b + n + 1, cmpByB);
    for (int i = 1; i <= n; i++) ans += p[i];
    for (int i = 1; i <= m; i++) ans -= b[i];
    std::cout << ans;
    return 0;
}