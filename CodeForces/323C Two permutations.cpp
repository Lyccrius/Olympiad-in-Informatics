#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e6;
const int maxM = 2e5;

int n;
int p[maxN + 10];
int q[maxN + 10];
int m;
int a, b, c, d;
int l1, r1, l2, r2;
int x;

int appear[maxN + 10];

int f(int z) {
    return ((z - 1 + x) % n) + 1;
}

struct Persistent {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int val;
    } node[maxN * 25];

    int ncnt;
    int root[maxN + 10];

    void Clone(int &xNode) {
        ncnt++;
        node[ncnt] = node[xNode];
        xNode = ncnt;
        return;
    }

    void Build(int &xNode, int l, int r) {
        Clone(xNode);
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) return;
        int mid = (l + r) / 2;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        return;
    }

    void Modify(int &xNode, int k) {
        Clone(xNode);
        node[xNode].val++;
        if (node[xNode].l == node[xNode].r) return;
        int mid = (node[xNode].l + node[xNode].r) / 2;
        if (mid >= k) Modify(node[xNode].lNode, k);
        else Modify(node[xNode].rNode, k);
        return;
    }

    int Query(int &xNode, int l, int r) {
        if (l > node[xNode].r || node[xNode].l > r) return 0;
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].val;
        return Query(node[xNode].lNode, l, r) + Query(node[xNode].rNode, l, r);
    }
} SGT;

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) std::cin >> q[i];
    for (int i = 1; i <= n; i++) appear[q[i]] = i;
    SGT.Build(SGT.root[0], 1, n);
    for (int i = 1; i <= n; i++) SGT.root[i] = SGT.root[i - 1], SGT.Modify(SGT.root[i], appear[p[i]]);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b >> c >> d;
        l1 = std::min(f(a), f(b));
        r1 = std::max(f(a), f(b));
        l2 = std::min(f(c), f(d));
        r2 = std::max(f(c), f(d));
        x = SGT.Query(SGT.root[r1], l2, r2) - SGT.Query(SGT.root[l1 - 1], l2, r2);
        std::cout << x << '\n';
        x++;
    }
    return 0;
}