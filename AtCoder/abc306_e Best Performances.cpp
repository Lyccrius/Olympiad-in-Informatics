#include <iostream>

typedef long long lxl;

const int maxN = 5e5;
const int maxQ = 5e5;
const int maxY = 1e9;
const int logY = 30;

int n, k, q;
int a[maxN + 10];
int x, y;

struct SegmentTree {
    struct Node {
        int cnt;
        lxl val;
        int lson;
        int rson;
    } node[(maxN + maxQ) * logY + 10];

    int root;
    int ncnt;

    void PushUp(int u) {
        node[u].cnt = node[node[u].lson].cnt + node[node[u].rson].cnt;
        node[u].val = node[node[u].lson].val + node[node[u].rson].val;
        return;
    }

    void Add(int &u, int l, int r, int pos, int val) {
        if (!u) u = ++ncnt;
        if (l == r) {
            node[u].cnt += val;
            node[u].val += val * l;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(node[u].lson, l, mid, pos, val);
        if (pos >= mid + 1) Add(node[u].rson, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    lxl Ask(int u, int l, int r, int k) {
        //printf("Ask(%d, [%d, %d], %d), cnt = %d, val = %d\n", u, l, r, k, node[u].cnt, node[u].val);
        //if (node[u].cnt >= k) return node[u].val;
        if (l == r) return 1ll * k * l;
        int mid = (l + r) / 2;
        if (node[node[u].rson].cnt >= k) return Ask(node[u].rson, mid + 1, r, k);
        return Ask(node[u].lson, l, mid, k - node[node[u].rson].cnt) + node[node[u].rson].val;
    }
} SGT;

int main() {
    std::cin >> n >> k >> q;
    for (int i = 1; i <= n; i++) SGT.Add(SGT.root, 0, maxY, 0, 1);
    for (int i = 1; i <= q; i++) {
        std::cin >> x >> y;
        SGT.Add(SGT.root, 0, maxY, a[x], -1);
        a[x] = y;
        SGT.Add(SGT.root, 0, maxY, a[x], 1);
        std::cout << SGT.Ask(SGT.root, 0, maxY, k) << '\n';
    }
    return 0;
}