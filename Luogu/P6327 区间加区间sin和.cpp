#include <iostream>
#include <iomanip>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cout << std::setiosflags(std::ios::fixed);
    return;
}

typedef long long lxl;
typedef double dbl;

const int maxN = 2e5;

int n;
int a[maxN + 10];
int m;
int opt, l, r; lxl v;

struct SegmentTree {
    struct Node {
        lxl tag;
        dbl sin;
        dbl cos;
    } node[maxN * 4 + 10];

    Node Merge(Node x, Node y) {
        Node ret;
        ret.tag = 0;
        ret.sin = x.sin + y.sin;
        ret.cos = x.cos + y.cos;
        return ret;
    }

    void PushUp(int u) {
        node[u] = Merge(node[u * 2], node[u * 2 + 1]);
        return;
    }

    void MakeTag(int u, lxl tag) {
        dbl s = node[u].sin;
        dbl c = node[u].cos;
        node[u].tag += tag;
        node[u].sin = s * std::cos(tag) + c * std::sin(tag);
        node[u].cos = c * std::cos(tag) - s * std::sin(tag);
        return;
    }

    void PushDown(int u) {
        MakeTag(u * 2, node[u].tag);
        MakeTag(u * 2 + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].sin = std::sin(a[l]);
            node[u].cos = std::cos(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int v) {
        if (s <= l && r <= t) {
            MakeTag(u, v);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Add(u * 2, l, mid, s, t, v);
        if (t >= mid + 1) Add(u * 2 + 1, mid + 1, r, s, t, v);
        PushUp(u);
        return;
    }

    double Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].sin;
        }
        PushDown(u);
        dbl ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret += Query(u * 2, l, mid, s, t);
        if (t >= mid + 1) ret += Query(u * 2 + 1, mid + 1, r, s, t);
        return ret;
    }
} SGT;

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; SGT.Build(1, 1, n);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> l >> r >> v;
            SGT.Add(1, 1, n, l, r, v);
        } else if (opt == 2) {
            std::cin >> l >> r;
            std::cout << std::setprecision(1) << SGT.Query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}