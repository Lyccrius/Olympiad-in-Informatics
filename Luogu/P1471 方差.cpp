#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 1e5;

int N, M;
double a[maxN + 10];
int opt, x, y;
double k;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        double sum;
        double pow;
        double tag;
    } node[maxN << 2];

    void PushUp(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[xNode].pow = node[lNode].pow + node[rNode].pow;
        node[xNode].sum = node[lNode].sum + node[rNode].sum;
        return;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[lNode].pow += node[xNode].tag * (node[lNode].r - node[lNode].l + 1) * node[xNode].tag + node[xNode].tag * node[lNode].sum * 2;
        node[rNode].pow += node[xNode].tag * (node[rNode].r - node[rNode].l + 1) * node[xNode].tag + node[xNode].tag * node[rNode].sum * 2;
        node[lNode].sum += node[xNode].tag * (node[lNode].r - node[lNode].l + 1);
        node[rNode].sum += node[xNode].tag * (node[rNode].r - node[rNode].l + 1);
        node[lNode].tag += node[xNode].tag;
        node[rNode].tag += node[xNode].tag;
        node[xNode].tag = 0;
        return;
    }

    void Build(int xNode, int l, int r) {
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) {
            node[xNode].sum = a[l];
            node[xNode].pow = a[l] * a[l];
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

    void Add(int xNode, int l, int r, double k) {
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].pow += k * (node[xNode].r - node[xNode].l + 1) * k + k * node[xNode].sum * 2;
            node[xNode].sum += k * (node[xNode].r - node[xNode].l + 1);
            node[xNode].tag += k;
            return;
        }
        if (node[xNode].tag) PushDown(xNode);
        if (l <= node[node[xNode].lNode].r) Add(node[xNode].lNode, l, r, k);
        if (r >= node[node[xNode].rNode].l) Add(node[xNode].rNode, l, r, k);
        PushUp(xNode);
        return;
    }

    double Query(int xNode, int l, int r) {
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].sum;
        if (node[xNode].tag) PushDown(xNode);
        double ret = 0;
        if (l <= node[node[xNode].lNode].r) ret += Query(node[xNode].lNode, l, r);
        if (r >= node[node[xNode].rNode].l) ret += Query(node[xNode].rNode, l, r);
        return ret;
    }

    double Query2(int xNode, int l, int r) {
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].pow;
        if (node[xNode].tag) PushDown(xNode);
        double ret = 0;
        if (l <= node[node[xNode].lNode].r) ret += Query2(node[xNode].lNode, l, r);
        if (r >= node[node[xNode].rNode].l) ret += Query2(node[xNode].rNode, l, r);
        return ret;
    }
} SGT;

int main() {
    //promote();
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    SGT.Build(1, 1, N);
    for (int i = 1; i <= M; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y >> k;
            SGT.Add(1, x, y, k);
        } else if (opt == 2) {
            std::cin >> x >> y;
            printf("%.4lf\n", SGT.Query(1, x, y) / (y - x + 1));
        } else {
            std::cin >> x >> y;
            double sum = SGT.Query(1, x, y) / (y - x + 1);
            double pow = SGT.Query2(1, x, y) / (y - x + 1);
            printf("%.4lf\n", pow - sum * sum);
        }
    }
    return 0;
}