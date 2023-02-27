#include <iostream>
#include <algorithm>

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
int x;

struct SegmentTree {
    struct Node {
        int l, r;
        int pre;
        int suf;
        int res;
        int len;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        int lson = u * 2;
        int rson = u * 2 + 1;
        node[u].l = node[lson].l;
        node[u].r = node[rson].r;
        node[u].pre = node[lson].pre;
        node[u].suf = node[rson].suf;
        node[u].len = node[lson].len + node[rson].len;
        node[u].res = std::max(node[lson].res, node[rson].res);
        if (node[lson].res == node[lson].len) if (node[lson].r != node[rson].l) node[u].pre = node[lson].len + node[rson].pre;
        if (node[rson].res == node[rson].len) if (node[lson].r != node[rson].l) node[u].suf = node[rson].len + node[lson].suf;
        if (node[lson].r != node[rson].l) node[u].res = std::max(node[u].res, node[lson].suf + node[rson].pre);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].l = 0;
            node[u].r = 0;
            node[u].pre = 1;
            node[u].suf = 1;
            node[u].res = 1;
            node[u].len = 1;
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid);
        Build(u * 2 + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int x) {
        if (l == r) {
            node[u].l = !node[u].l;
            node[u].r = !node[u].r;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) Modify(u * 2, l, mid, x);
        if (x >= mid + 1) Modify(u * 2 + 1, mid + 1, r, x);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r) {
        return node[u].res;
    }
} SGT;

int main() {
    std::cin >> n >> q;
    SGT.Build(1, 1, n);
    for (int i = 1; i <= q; i++) {
        std::cin >> x;
        SGT.Modify(1, 1, n, x);
        std::cout << SGT.Query(1, 1, n) << '\n';
    }
    return 0;
}