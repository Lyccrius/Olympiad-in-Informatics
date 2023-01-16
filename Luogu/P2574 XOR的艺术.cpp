#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2e5;
const int maxM = 2e5;

int n, m;
int c, a, b;
int s[maxN + 10];

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int val;
        int tag;
    } node[maxN << 2];

    void PushUp(int xNode) {
        node[xNode].val = node[node[xNode].lNode].val + node[node[xNode].rNode].val;
        return;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[lNode].val = node[lNode].r - node[lNode].l + 1 - node[lNode].val;
        node[rNode].val = node[rNode].r - node[rNode].l + 1 - node[rNode].val;
        node[lNode].tag ^= 1;
        node[rNode].tag ^= 1;
        node[xNode].tag ^= 1;
        return;
    }

    void Build(int xNode, int l, int r) {
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) {
            node[xNode].val = s[l];
            return;
        }
        int mid = (l + r) >> 1;
        node[xNode].lNode = xNode * 2;
        node[xNode].rNode = xNode * 2 + 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        PushUp(xNode);
        return;
    }

    void Modify(int xNode, int l, int r) {
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].val = node[xNode].r - node[xNode].l + 1 - node[xNode].val;
            node[xNode].tag ^= 1;
            return;
        }
        if (node[xNode].tag) PushDown(xNode);
        if (l <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, l, r);
        if (r >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, l, r);
        PushUp(xNode);
        return;
    }

    int Query(int xNode, int l, int r) {
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].val;
        int ret = 0;
        if (node[xNode].tag) PushDown(xNode);
        if (l <= node[node[xNode].lNode].r) ret += Query(node[xNode].lNode, l, r);
        if (r >= node[node[xNode].rNode].l) ret += Query(node[xNode].rNode, l, r);
        return ret; 
    }
} SGT;

int main() {
    //promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%1d", &s[i]);
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> c >> a >> b;
        if (c == 0) SGT.Modify(1, a, b);
        else std::cout << SGT.Query(1, a, b) << '\n';
    }
    return 0;
}