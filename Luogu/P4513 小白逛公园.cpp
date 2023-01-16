#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int inf = 1e9;

const int maxN = 5e5;
const int maxM = 1e5;

int n, m;
int sco[maxN + 10];
int k;
int a, b;
int p, s;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int val;
        int res;
        int pre;
        int suf;
    } node[maxN << 2];

    void PushUp(Node &xNode, Node lNode, Node rNode) {
        xNode.res = std::max(lNode.res, rNode.res);
        xNode.res = std::max(lNode.suf + rNode.pre, xNode.res);
        xNode.res = std::max(lNode.val + rNode.pre, xNode.res);
        xNode.res = std::max(lNode.suf + rNode.val, xNode.res);
        xNode.res = std::max(lNode.val + rNode.val, xNode.res);
        xNode.pre = std::max(lNode.val + rNode.pre, lNode.pre);
        xNode.suf = std::max(lNode.suf + rNode.val, rNode.suf);
        xNode.val = lNode.val + rNode.val;
        return;
    }

    void Build(int xNode, int l, int r) {
        //printf("Building %d, [%d, %d]\n", xNode, l, r);
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) {
            node[xNode].val = sco[l];
            node[xNode].res = sco[l];
            node[xNode].pre = sco[l];
            node[xNode].suf = sco[l];
            return;
        }
        int mid = (l + r) >> 1;
        node[xNode].lNode = xNode * 2;
        node[xNode].rNode = xNode * 2 + 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        PushUp(node[xNode], node[node[xNode].lNode], node[node[xNode].rNode]);
        return;
    }

    void Modify(int xNode, int p, int s) {
        if (p == node[xNode].l && node[xNode].r == p) {
            node[xNode].val = s;
            node[xNode].res = s;
            node[xNode].pre = s;
            node[xNode].suf = s;
            return;
        }
        if (p <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, p, s);
        if (p >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, p, s);
        PushUp(node[xNode], node[node[xNode].lNode], node[node[xNode].rNode]);
        return;
    }

    Node Query(int xNode, int a, int b) {
        //printf("Querying %d, [%d, %d]\n", xNode, node[xNode].l, node[xNode].r);
        if (a <= node[xNode].l && node[xNode].r <= b) return node[xNode];
        if (b <= node[node[xNode].lNode].r) return Query(node[xNode].lNode, a, b);
        if (a >= node[node[xNode].rNode].l) return Query(node[xNode].rNode, a, b);
        Node ret;
        Node lNode = Query(node[xNode].lNode, a, b);
        Node rNode = Query(node[xNode].rNode, a, b);
        PushUp(ret, lNode, rNode);
        return ret;
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> sco[i];
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> k;
        if (k == 1) {
            std::cin >> a >> b;
            if (a > b) std::swap(a, b);
            std::cout << SGT.Query(1, a, b).res << '\n';
        } else {
            std::cin >> p >> s;
            SGT.Modify(1, p, s);
        }
    }
    return 0;
}