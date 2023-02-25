#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef unsigned long long lxl;

const int maxN = 5e5;
const int maxM = 5e5;
const lxl inf = 1e18;

int n, m;
lxl a[maxN + 10];
int opt;
lxl x, y;
int l, r;

struct SegmentTree {
    struct Node {
        lxl min;
        lxl max;
        lxl sum;
        lxl pow;
    } node[maxN * 4 + 10];

    Node Merge(Node x, Node y) {
        Node ret;
        ret.min = std::min(x.min, y.min);
        ret.max = std::max(x.max, y.max);
        ret.sum = x.sum + y.sum;
        ret.pow = x.pow + y.pow;
        return ret;
    }

    void PushUp(int u) {
        node[u] = Merge(node[u * 2], node[u * 2 + 1]);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].min = a[l];
            node[u].max = a[l];
            node[u].sum = a[l];
            node[u].pow = a[l] * a[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int pos, lxl val) {
        if (l == r) {
            node[u].min = val;
            node[u].max = val;
            node[u].sum = val;
            node[u].pow = val * val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    Node Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u];
        Node ret;
        ret.min = inf;
        ret.max = 0;
        ret.sum = 0;
        ret.pow = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret = Merge(ret, Query(u * 2, l, mid, s, t));
        if (t >= mid + 1) ret = Merge(ret, Query(u * 2 + 1, mid + 1, r, s, t));
        return ret;
    }
} SGT;

lxl sum(lxl x) {
    return x * (x + 1) / 2;
}

lxl pow(lxl x) {
    return x * (x + 1) * (2 * x + 1);
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y;
            SGT.Modify(1, 1, n, x, y);
        } else {
            std::cin >> l >> r;
            SegmentTree::Node res = SGT.Query(1, 1, n, l, r);
            if (sum(res.max) - sum(res.min - 1) != res.sum || pow(res.max) - pow(res.min - 1) != res.pow * 6) std::cout << "yuanxing\n";
            else std::cout << "damushen\n";
        }
    }
    return 0;
}