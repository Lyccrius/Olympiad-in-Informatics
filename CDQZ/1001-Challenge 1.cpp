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
        int lson;
        int rson;
    } node[maxN * 4 + maxM * logN + 10];

    int ncnt;
    int root[maxM + 10];

    int Clone(int u) {
        ncnt++;
        node[ncnt] = node[u];
        return ncnt;
    }

    void Build(int &u, int l, int r) {
        u = Clone(u);
        if (l == r) {
            node[u].val = a[l];
            return;
        }
        int mid = (l + r) / 2;
        Build(node[u].lson, l, mid);
        Build(node[u].rson, mid + 1, r);
        return;
    }

    void Modify(int &u, int l, int r, int pos, int val) {
        u = Clone(u);
        if (l == r) {
            node[u].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(node[u].lson, l, mid, pos, val);
        if (pos >= mid + 1) Modify(node[u].rson, mid + 1, r, pos, val);
        return;
    }

    int Query(int u, int l, int r, int pos) {
        if (l == r) {
            return node[u].val;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) return Query(node[u].lson, l, mid, pos);
        if (pos >= mid + 1) return Query(node[u].rson, mid + 1, r, pos);
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(SGT.root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        SGT.root[i] = SGT.root[i - 1];
        std::cin >> op;
        if (op == 'M') {
            std::cin >> x >> y;
            SGT.Modify(SGT.root[i], 1, n, x, y);
        } else if (op == 'Q') {
            std::cin >> x >> y;
            std::cout << SGT.Query(SGT.root[y], 1, n, x) << '\n';
        }
    }
    return 0;
}