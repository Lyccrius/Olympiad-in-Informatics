#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a[maxN + 10];
char op; int x, y, z;

struct SegmentTree {
    struct Node {
        lxl val;
        lxl tag;
        lxl tav;
    } node[maxN * 4 + 10];

    void MakeTag(int u, int l, int r, lxl tag) {
        node[u].val = tag * (r - l + 1);
        node[u].tav = tag;
        node[u].tag = true;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void PushDown(int u, int l, int r) {
        int mid = (l + r) / 2;
        if (!node[u].tag) return;
        MakeTag(u * 2, l, mid, node[u].tav);
        MakeTag(u * 2 + 1, mid + 1, r, node[u].tav);
        node[u].tag = false;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = a[l];
            node[u].tag = false;
            node[u].tav = 0;
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, lxl val) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t, val);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        int ret = 0;
        if (s <= mid) ret += Query(u * 2, l, mid, s, t);
        if (t >= mid + 1) ret += Query(u * 2 + 1, mid + 1, r, s, t);
        return ret;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 'M') {
            std::cin >> x >> y >> z;
            SGT.Modify(1, 1, n, x, y, z);
        } else if (op == 'Q') {
            std::cin >> x >> y;
            std::cout << SGT.Query(1, 1, n, x, y) << '\n';
        }
    }
    return 0;
}