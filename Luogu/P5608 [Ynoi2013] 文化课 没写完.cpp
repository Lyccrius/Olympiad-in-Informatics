#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;
const lxl mod = 1e9 + 7;

int n, m;
lxl a[maxN + 10];
lxl p[maxN + 10];
lxl op, l, r, x, y;

lxl pow(lxl a, lxl b) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b = b / 2;
    }
    return ret;
}

struct SegmentTree {
    struct Node {
        lxl a;
        lxl p;
        lxl all;
        lxl sum;
        lxl mul;
        lxl pre;
        lxl prl;
        lxl suf;
        lxl sul;
        lxl taa;
        lxl tap;
        lxl res;
    } node[4 * maxN + 10];

    Node Merge(Node a, Node b) {
        Node ret;
        ret.a = b.a;
        ret.p = b.p;
        if (a.all == b.all) ret.all = a.all;
        else ret.all = -1;
        ret.sum = (a.sum + b.sum) % mod;
        ret.mul = a.mul * b.mul % mod;
        if (a.all == 1) {
            ret.pre = a.mul * b.pre % mod;
            ret.prl = a.sul + b.prl;
        } else {
            ret.pre = a.pre;
            ret.prl = a.prl;
        }
        if (b.all == 1) {
            ret.suf = a.suf * b.mul % mod;
            ret.sul = a.sul + b.sul;
        } else {
            ret.suf = b.suf;
            ret.sul = b.sul;
        }
        ret.taa = -1;
        ret.tap = -1;
        if (a.p == 0) ret.res = (a.res + b.res) % mod;
        else ret.res = ((a.res - a.suf + a.suf * b.pre % mod - b.pre + b.res) % mod + mod) % mod;
        return ret;
    }

    void MakeTagA(int u, int l, int r, lxl tag) {
        node[u].sum = tag * (r - l + 1) % mod;
        node[u].mul = pow(tag, 1ll * (r - l + 1)) % mod;
        node[u].pre = pow(tag, node[u].prl) % mod;
        node[u].suf = pow(tag, node[u].sul) % mod;
        node[u].taa = tag;
        return;
    }

    void MakeTagP(int u, lxl tag) {

    }

    void PushUp(int u) {
        node[u] = Merge(node[2 * u], node[2 * u + 1]);
        return;
    }

    void PushDown(int u, int l, int r) {
        int mid = (l + r) / 2;
        if (node[u].taa != -1) {
            MakeTagA(2 * u, l, mid, node[u].taa);
            MakeTagA(2 * u + 1, mid + 1, r, node[u].taa);
            node[u].taa = -1;
        }
        if (node[u].tap != -1) {
            MakeTagP(2 * u, node[u].tap);
            MakeTagP(2 * u + 1, node[u].tap);
            node[u].tap = -1;
        }
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].a = a[l];
            node[u].p = p[l];
            node[u].all = p[l];
            node[u].sum = a[l];
            node[u].mul = a[l];
            node[u].pre = a[l];
            node[u].prl = 1;
            node[u].suf = a[l];
            node[u].sul = 1;
            node[u].taa = -1;
            node[u].tap = -1;
            node[u].res = a[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void ModifyA(int u, int l, int r, int s, int t, lxl val) {
        if (s <= l && r <= t) {
            MakeTagA(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) ModifyA(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) ModifyA(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    void ModifyP(int u, int l, int r, int s, int t, lxl val) {
        if (s <= l && r <= t) {
            MakeTagP(u, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) ModifyP(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) ModifyP(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    Node QueryW(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u];
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return QueryW(2 * u, l, mid, s, t);
        if (s >= mid + 1) return QueryW(2 * u + 1, mid + 1, r, s, t);
        return Merge(QueryW(2 * u, l, mid, s, t), QueryW(2 * u + 1, mid + 1, r, s, t));
    }
}  SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) a[i] = a[i] % mod;
    for (int i = 1; i < n; i++) std::cin >> p[i];
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> l >> r >> x; x = x % mod;
            SGT.ModifyA(1, 1, n, l, r, x);
        } else if (op == 2) {
            std::cin >> l >> r >> y;
            SGT.ModifyP(1, 1, n, l, r, y);
        } else if (op == 3) {
            std::cin >> l >> r;
            std::cout << SGT.QueryW(1, 1, n, l, r).res << '\n';
        }
    }
    return 0;
}