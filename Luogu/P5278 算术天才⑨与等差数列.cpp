#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef unsigned long long lxl;

const int maxN = 3e5;

int n, m;
lxl a[maxN + 10];
int op;
lxl x, y;
lxl l, r, k;
int yes;

struct SegmentTree {
    struct Node {
        lxl val;
        lxl pow;
        lxl min;
        lxl max;
    } node[maxN * 4 + 10];

    Node Merge(Node a, Node b) {
        Node ret;
        ret.val = a.val + b.val;
        ret.pow = a.pow + b.pow;
        ret.min = std::min(a.min, b.min);
        ret.max = std::max(a.max, b.max);
        return ret;
    }

    void PushUp(int u) {
        node[u] = Merge(node[u * 2], node[u * 2 + 1]);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = a[l];
            node[u].pow = a[l] * a[l];
            node[u].min = a[l];
            node[u].max = a[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, lxl pos, lxl val) {
        if (l == r) {
            node[u].val = val;
            node[u].pow = val * val;
            node[u].min = val;
            node[u].max = val;
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
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Merge(Query(u * 2, l, mid, s, t), Query(u * 2 + 1, mid + 1, r, s, t));
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y; x ^= yes; y ^= yes;
            SGT.Modify(1, 1, n, x, y);
        } else if (op == 2) {
            std::cin >> l >> r >> k; l ^= yes; r ^= yes; k ^= yes; //if (l > r) std::swap(l, r);
            SegmentTree::Node res = SGT.Query(1, 1, n, l, r);
            /*if (k == 0) {
                if (res.min != res.max) {
                    std::cout << "No" << '\n';
                } else {
                    std::cout << "Yes" << '\n';
                    yes++;
                }
            } else {*/
                lxl len = r - l + 1;
                lxl dif = k * (len - 1);
                lxl sum = (res.min + res.max) * len / 2;
                if (dif != res.max - res.min || sum != res.val) {
                    std::cout << "No" << '\n';
                } else {
                    std::cout << "Yes" << '\n';
                    yes++;
                }
            //}
        }
    }
    return 0;
}