#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 2e5;
const int maxQ = 2e5;
const int minD = 0;
const int maxD = 1e9;
const int logD = 30;

int n, q;
int s, t, x;
int d;

struct SegmentTree {
    struct Node {
        int val;
        int tag;
        int lson;
        int rson;

        Node() {
            val = maxD + 10;
            return;
        }
    } node[2 * maxN * logD + 10];

    int root;
    int ncnt;

    void MakeTag(int u, int val) {
        if (node[u].val < val) return;
        node[u].val = val;
        node[u].tag = val;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        int &l = node[u].lson;
        int &r = node[u].rson;
        if (!l) l = ++ncnt;
        if (!r) r = ++ncnt;
        MakeTag(l, node[u].tag);
        MakeTag(r, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = std::min(node[node[u].lson].val, node[node[u].rson].val);
        return;
    }

    void Modify(int &u, int l, int r, int s, int t, int val) {
        if (!u) u = ++ncnt;
        s = std::max(s, minD);
        //t = std::max(t, minD);
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(node[u].lson, l, mid, s, t, val);
        if (t >= mid + 1) Modify(node[u].rson, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int pos) {
        if (!u) return maxD + 10;
        if (l == r) {
            return node[u].val;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (pos <= mid) return Query(node[u].lson, l, mid, pos);
        if (pos >= mid + 1) return Query(node[u].rson, mid + 1, r, pos);
    }
} SGT;

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> s >> t >> x;
        SGT.Modify(SGT.root, minD, maxD, s - x, t - 1 - x, x);
    }
    for (int i = 1; i <= q; i++) {
        std::cin >> d;
        int res = SGT.Query(SGT.root, minD, maxD, d);
        if (res > maxD) res = -1;
        std::cout << res << '\n';
    }
    return 0;
}