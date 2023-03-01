#include <iostream>

const int maxM = 1e5;
const int logM = 17;

int n, m;
char op; int x;

struct SegmentTree {
    struct Node {
        int val;
        int lson;
        int rson;
    } node[maxM * 4 + maxM * logM + 10];

    int ncnt;
    int root[maxM + 10];
    int head[maxM + 10];

    int Clone(int u) {
        ncnt++;
        node[ncnt] = node[u];
        return ncnt;
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
    std::cin >> m; n = m;
    for (int i = 1; i <= m; i++) {
        SGT.root[i] = SGT.root[i - 1];
        SGT.head[i] = SGT.head[i - 1];
        std::cin >> op;
        if (op == 'A') {
            std::cin >> x;
            SGT.head[i]++;
            SGT.Modify(SGT.root[i], 1, n, SGT.head[i], x);
        } else if (op == 'Q') {
            std::cin >> x;
            std::cout << SGT.Query(SGT.root[i], 1, n, x) << '\n';
            i--; m--;
        } else if (op == 'U') {
            std::cin >> x;
            SGT.root[i] = SGT.root[i - x - 1];
            SGT.head[i] = SGT.head[i - x - 1];
        }
    }
    return 0;
}