#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;
const lxl mod = 1000000007;

int n, m;
lxl a[maxN + 10];
char op; lxl x, y;

struct SegmentTree {
    struct Node {
        lxl val;
        lxl l, r;
        lxl res2;
        lxl res3;
    } node[maxN * 4 + 10];

    Node Merge(Node u, Node v) {
        Node ret;
        ret.val = (u.val + v.val) % mod;
        ret.l = u.l;
        ret.r = v.r;
        ret.res2 = ((u.res2 + v.res2) % mod + 1ll * u.val * v.val % mod) % mod;
        ret.res3 = ((u.res3 + v.res3) % mod + 1ll * u.r * v.l % mod) % mod;
        return ret;
    }

    void PushUp(int u) {
        node[u] = Merge(node[u * 2], node[u * 2 + 1]);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = a[l] % mod;
            node[u].l = a[l] % mod;
            node[u].r = a[l] % mod;
            node[u].res2 = 0;
            node[u].res3 = 0;
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val = val % mod;
            node[u].l = val % mod;
            node[u].r = val % mod;
            node[u].res2 = 0;
            node[u].res3 = 0;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    Node Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u];
        }
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Merge(Query(u * 2, l, mid, s, t), Query(u * 2 + 1, mid + 1, r, s, t));
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 'M') {
            std::cin >> x >> y;
            SGT.Modify(1, 1, n, x, (y % mod + mod) % mod);
        } else if (op == 'Q') {
            std::cin >> x >> y;
            std::cout << (SGT.Query(1, 1, n, x, y).res2 % mod + mod) % mod << '\n';
        } else if (op == 'A') {
            std::cin >> x >> y;
            std::cout << (SGT.Query(1, 1, n, x, y).res3 % mod + mod) % mod << '\n';
        }
    }
    return 0;
}