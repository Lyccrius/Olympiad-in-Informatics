#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long lxl;

const lxl maxN = 1e5;
const lxl maxM = 1e5;

lxl n;
lxl a[maxN + 10];
lxl m;
lxl k, l, r;

struct SegmentTree {
    struct Node {
        lxl lson;
        lxl rson;
        lxl val;
        lxl top;
    } node[maxN * 4 + 10];

    lxl ncnt;
    lxl root;

    void PushUp(lxl u) {
        lxl l = node[u].lson;
        lxl r = node[u].rson;
        node[u].val = node[l].val + node[r].val;
        node[u].top = std::max(node[l].top, node[r].top);
        return;
    }

    void Build(lxl &u, lxl l, lxl r) {
        u = ++ncnt;
        if (l == r) {
            node[u].val = a[l];
            node[u].top = a[l];
            return;
        }
        lxl mid = (l + r) / 2;
        Build(node[u].lson, l, mid);
        Build(node[u].rson, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(lxl u, lxl l, lxl r, lxl s, lxl t) {
        if (l == r) {
            node[u].val = std::sqrt(node[u].val);
            node[u].top = std::sqrt(node[u].top);
            return;
        }
        lxl mid = (l + r) / 2;
        if (s <= mid) if (node[node[u].lson].top > 1) Modify(node[u].lson, l, mid, s, t);
        if (t >= mid + 1) if (node[node[u].rson].top > 1) Modify(node[u].rson, mid + 1, r, s, t);
        PushUp(u);
        return;
    }

    lxl Query(lxl u, lxl l, lxl r, lxl s, lxl t) {
        if (s > r || l > t) return 0;
        if (s <= l && r <= t) return node[u].val;
        lxl mid = (l + r) / 2;
        lxl ret = 0;
        if (s <= mid) ret += Query(node[u].lson, l, mid, s, t);
        if (t >= mid + 1) ret += Query(node[u].rson, mid + 1, r, s, t);
        return ret;
    }
} SGT;

int main() {
    std::cin >> n;
    for (lxl i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(SGT.root, 1, n);
    std::cin >> m;
    for (lxl i = 1; i <= m; i++) {
        std::cin >> k >> l >> r;
        if (l > r) std::swap(l, r);
        if (k == 0) {
            SGT.Modify(SGT.root, 1, n, l, r);
        }
        if (k == 1) {
            std::cout << SGT.Query(SGT.root, 1, n, l, r) << '\n';
        }
    }
    return 0;
}