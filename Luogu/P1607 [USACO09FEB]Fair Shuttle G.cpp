#include <cstdio>
#include <algorithm>

const int inf = 0x3f3f3f3f;
const int maxK = 50000 + 10;
const int maxN = 20000 + 10;

int K, N, C;

struct Cow {
    int S;
    int E;
    int M;
    bool operator<(Cow other) const {
        return E < other.E;
    }
};
Cow cows[maxK];

namespace Shuttle {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int value;
        int tag;
    };

    Node node[maxN << 2];

    void PushUp(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[xNode].value = std::min(node[lNode].value, node[rNode].value);
        return;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[lNode].value -= node[xNode].tag;
        node[rNode].value -= node[xNode].tag;
        node[lNode].tag += node[xNode].tag;
        node[rNode].tag += node[xNode].tag;
        node[xNode].tag = 0;
        return;
    }

    void Build(int xNode, int l, int r) {
        node[xNode].l = l;
        node[xNode].r = r;
        node[xNode].value = C;
        if (l == r) return;
        int mid = (l + r) / 2;
        node[xNode].lNode = xNode * 2;
        node[xNode].rNode = xNode * 2 + 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        PushUp(xNode);
        return;
    }

    int Query(int xNode, int l, int r) {
        if (l <= node[xNode].l &&
            r >= node[xNode].r) return node[xNode].value;

        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        int res = inf;
        if (node[xNode].tag) PushDown(xNode);
        if (l <= node[lNode].r) res = std::min(res, Query(lNode, l, r));
        if (r >= node[rNode].l) res = std::min(res, Query(rNode, l, r));
        PushUp(xNode);
        return res;
    }

    void Modify(int xNode, int l, int r, int value) {
        if (node[xNode].l >= l &&
            node[xNode].r <= r) {
            node[xNode].value -= value;
            node[xNode].tag += value;
            return;
        }

        if (node[xNode].tag) PushDown(xNode);
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        if (l <= node[lNode].r) Modify(lNode, l, r, value);
        if (r >= node[rNode].l) Modify(rNode, l, r, value);
        PushUp(xNode);
        return;
    }
};

int main() {
    scanf("%d%d%d", &K, &N, &C);
    Shuttle::Build(1, 1, N);
    for (int i = 1; i <= K; i++) scanf("%d%d%d", &cows[i].S, &cows[i].E, &cows[i].M);
    std::sort(cows + 1, cows + K + 1);
    int ans = 0;
    for (int i = 1; i <= K; i++) {
        int ride = Shuttle::Query(1, cows[i].S, cows[i].E - 1);
        ride = std::min(ride, cows[i].M);
        if (ride > 0) {
            Shuttle::Modify(1, cows[i].S, cows[i].E - 1, ride);
            ans += ride;
        }
    }
    printf("%d\n", ans);
    return 0;
}