#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;
const int logN = 17;

int n, m;
int a[maxN + 10];
char op; int x, y;

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = a[l];
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
            node[u].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret += Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) ret += Query(u * 2 + 1, mid + 1, r, s, t);
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
            std::cin >> x >> y;
            SGT.Modify(1, 1, n, x, y);
        } else if (op == 'Q') {
            std::cin >> x >> y;
            std::cout << SGT.Query(1, 1, n, x, y) << '\n';
        }
    }
    return 0;
}