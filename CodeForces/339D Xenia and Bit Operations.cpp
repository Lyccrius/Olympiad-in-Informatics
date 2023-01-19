#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 17;
const int maxM = 1e5;

int n, m;
int a[(1 << maxN) + 10];
int p[maxM + 10], b[maxM + 10];

struct SegmentTree {
    struct Node {
        int lson;
        int rson;
        int dep;
        int val;
    } node[(1 << maxN) * 4 + 10];

    int ncnt;
    int root;

    void PushUp(int u) {
        node[u].dep = node[node[u].lson].dep + 1;
        if (node[u].dep & 1) node[u].val = node[node[u].lson].val | node[node[u].rson].val;
        else node[u].val = node[node[u].lson].val ^ node[node[u].rson].val;
        return;
    }

    void Build(int &u, int l, int r) {
        u = ++ncnt;
        if (l == r) {
            node[u].val = a[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(node[u].lson, l, mid);
        Build(node[u].rson, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int p, int v) {
        if (l == r) {
            node[u].val = v;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid) Modify(node[u].lson, l, mid, p, v);
        else Modify(node[u].rson, mid + 1, r, p, v);
        PushUp(u);
    }

    int Query() {
        return node[root].val;
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m;
    n = 1 << n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(SGT.root, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> p[i] >> b[i];
        SGT.Modify(SGT.root, 1, n, p[i], b[i]);
        std::cout << SGT.Query() << '\n';
    }
    return 0;
}