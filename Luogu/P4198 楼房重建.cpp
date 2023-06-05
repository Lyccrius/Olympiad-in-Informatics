#include <iostream>

typedef double dbl;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int x, y;
dbl a[maxN + 10];

struct SegmentTree {
    struct Node {
        dbl max;
        int res;
    } node[4 * maxN + 10];

    int Update(int u, int l, int r, dbl max) {
        if (max >= node[u].max) return 0;
        if (max < a[l]) return node[u].res;
        if (l == r) return 0;
        int mid = (l + r) / 2;
        if (max >= node[2 * u].max) return Update(2 * u + 1, mid + 1, r, max);
        return Update(2 * u, l, mid, max) + node[u].res - node[2 * u].res;
    }

    void PushUp(int u, int l, int r) {
        int mid = (l + r) / 2;
        node[u].max = std::max(node[2 * u].max, node[2 * u + 1].max);
        node[u].res = node[2 * u].res + Update(2 * u + 1, mid + 1, r, node[2 * u].max);
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].max = a[pos];
            node[u].res = 1;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(2 * u, l, mid, pos, val);
        if (pos >= mid + 1) Modify(2 * u + 1, mid + 1, r, pos, val);
        PushUp(u, l, r);
        return;
    }

    void Query(int u, int l, int r) {
        std::cout << node[u].res << '\n';
        return;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        a[x] = 1.0 * y / x;
        SGT.Modify(1, 1, n, x, y);
        SGT.Query(1, 1, n);
    }
    return 0;
}