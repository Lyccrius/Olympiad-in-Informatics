#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;

int N, M;
lxl a[maxN + 10];
lxl s[maxN + 10];
char opt[10];
lxl p, x;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        lxl val;
        lxl tag;
    } node[maxN << 2];

    void PushUp(int xNode) {
        node[xNode].val = node[node[xNode].lNode].val + node[node[xNode].rNode].val;
        return;
    }

    void Mark(int xNode, lxl val) {
        node[xNode].val += val * (node[xNode].r - node[xNode].l + 1);
        node[xNode].tag += val;
        return;
    }

    void PushDown(int xNode) {
        if (node[xNode].tag == 0) return;
        Mark(node[xNode].lNode, node[xNode].tag);
        Mark(node[xNode].rNode, node[xNode].tag);
        node[xNode].tag = 0;
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

    void Modify(int xNode, int l, int r, lxl x) {
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].val += x * (node[xNode].r - node[xNode].l + 1);
            node[xNode].tag += x;
            return;
        }
        PushDown(xNode);
        if (l <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, l, r, x);
        if (r >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, l, r, x);
        PushUp(xNode);
        return;
    }

    lxl Query(int xNode, int l, int r) {
        if (l > node[xNode].r || node[xNode].l > r) return 0;
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].val;
        PushDown(xNode);
        return Query(node[xNode].lNode, l, r) + Query(node[xNode].rNode, l, r);
    }
} SGT;

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) s[i] = s[i - 1] + a[i];
    SGT.Build(1, 1, N);
    for (int i = 1; i <= M; i++) {
        std::cin >> opt;
        if (opt[0] == 'M') std::cin >> p >> x, SGT.Modify(1, p, N, x - a[p]), a[p] = x;
        else std::cin >> p, std::cout << SGT.Query(1, 1, p) << '\n';
    }
    return 0;
}