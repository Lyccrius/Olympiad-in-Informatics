#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e9;
const int maxQ = 3e5;
const int logN = 50;

int n, q;
int l, r, k;

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int val;
        int tag;
    } node[maxQ * logN + 10];

    int ncnt;
    int root;

    void Build(int &u) {
        u = ++ncnt;
        return;
    }

    void MakeTag(int &u, int l, int r, int val) {
        if (!u) Build(u);
        node[u].tag = val;
        node[u].val = (val - 1) * (r - l + 1);
        return;
    }

    void PushDown(int u, int l, int r) {
        if (!node[u].tag) return;
        int mid = (l + r) / 2;
        MakeTag(node[u].lson, l, mid, node[u].tag);
        MakeTag(node[u].rson, mid + 1, r, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[node[u].lson].val + node[node[u].rson].val;
        return;
    }

    void Modify(int &u, int l, int r, int s, int t, int val) {
        if (!u) Build(u);
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(node[u].lson, l, mid, s, t, val);
        if (t >= mid + 1) Modify(node[u].rson, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (!u) return 0;
        if (s <= l && r <= t) {
            return node[u].val;
        }
    }
} SGT;

int main() {
    promote();
    std::cin >> n;
    std::cin >> q;
    SGT.Modify(SGT.root, 1, n, 1, n, 2);
    for (int i = 1; i <= q; i++) {
        std::cin >> l >> r >> k;
        SGT.Modify(SGT.root, 1, n, l, r, k);
        std::cout << SGT.Query(SGT.root, 1, n, 1, n) << '\n';
    }
    return 0;
}