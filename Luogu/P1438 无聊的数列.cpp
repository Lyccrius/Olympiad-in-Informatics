#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2e5;
const int maxM = 1e5;

int n, m;
long long a[maxN + 10];
int opt;
long long l, r, K, D;
int p;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        long long val;
        int tag;
        long long K;
        long long D;
    } node[maxN << 2];

    void PushUp(int xNode) {
        node[xNode].val = node[node[xNode].lNode].val + node[node[xNode].rNode].val;
        return;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        long long len = node[lNode].r - node[lNode].l + 1;
        node[lNode].tag = true;
        node[rNode].tag = true;
        node[xNode].tag = false;
        node[lNode].K += node[xNode].K;
        node[rNode].K += node[xNode].K + len * node[xNode].D;
        node[lNode].D += node[xNode].D;
        node[rNode].D += node[xNode].D;
        node[xNode].K = 0;
        node[xNode].D = 0;
        //printf("(%d, %d) K = %d, D = %d\n", node[lNode].l, node[lNode].r, node[lNode].K, node[lNode].D);
        //printf("(%d, %d) K = %d, D = %d\n", node[rNode].l, node[rNode].r, node[rNode].K, node[rNode].D);
        return;
    }

    void Build(int xNode, int l, int r) {
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) {
            node[xNode].val = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        node[xNode].lNode = xNode * 2;
        node[xNode].rNode = xNode * 2 + 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        //PushUp(xNode);
        return;
    }

    void Modify(int xNode, int l, int r, long long K, long long D) {
        if (l <= node[xNode].l && node[xNode].r <= r) {
            //printf("Modify %d, %d, %d, %d\n", node[xNode].l, node[xNode].r, K, D);
            node[xNode].tag = true;
            node[xNode].K += K + (node[xNode].l - l) * D;
            node[xNode].D += D;
            return;
        }
        if (node[xNode].tag) PushDown(xNode);
        if (l <= node[node[xNode].lNode].r) Modify(node[xNode].lNode, l, r, K, D);
        if (r >= node[node[xNode].rNode].l) Modify(node[xNode].rNode, l, r, K, D);
        //PushUp(xNode);
        return;
    }

    long long Query(int xNode, int p) {
        if (node[xNode].l == node[xNode].r) return node[xNode].val + node[xNode].K;
        if (node[xNode].tag) PushDown(xNode);
        long long ret = 0;
        if (p <= node[node[xNode].lNode].r) ret += Query(node[xNode].lNode, p);
        if (p >= node[node[xNode].rNode].l) ret += Query(node[xNode].rNode, p);
        ret += node[xNode].K;
        ret += node[xNode].D * (p - node[xNode].l);
        return ret;
    }
} SGT;

int main() {
    //freopen("P1438_2.in", "r", stdin);
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) std::cin >> l >> r >> K >> D, SGT.Modify(1, l, r, K, D);
        else std::cin >> p, std::cout << SGT.Query(1, p) << '\n';
        for (int i = 1; i <= n; i++) {
        //    std::cout << SGT.Query(1, i) << " ";
        }
        //std::cout << '\n';
    }
    return 0;
}