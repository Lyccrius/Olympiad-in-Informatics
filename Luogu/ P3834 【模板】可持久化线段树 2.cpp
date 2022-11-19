#include <cstdio>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 2e5 + 10;

int n, m;
int a[maxN];

namespace PresidentTree {
    struct Node {
        int l;
        int r;
        int cnt;
        int lNode;
        int rNode;
    };

    int root[maxN];
    Node node[maxN * 28];
    int cnt;

    void Build(int &xNode, int l, int r) {
        cnt++;
        xNode = cnt;
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) return;
        int mid = (l + r) / 2;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        return;
    }

    int Clone(int &xNode) {
        cnt++;
        node[cnt] = node[xNode];
        return cnt;
    }

    void Modify(int &xNode, int value) {
        xNode = Clone(xNode);
        node[xNode].cnt++;
        if (node[xNode].l == node[xNode].r) return;
        int mid = (node[xNode].l + node[xNode].r) / 2;
        if (value <= mid) Modify(node[xNode].lNode, value);
        else Modify(node[xNode].rNode, value);
        return;
    }

    int Query(int xNode, int yNode, int k) {
        if (node[xNode].l == node[xNode].r) return node[xNode].l;
        int mid = (node[xNode].l + node[xNode].r) / 2;
        int dif = node[node[yNode].lNode].cnt - node[node[xNode].lNode].cnt;
        if (dif >= k) return Query(node[xNode].lNode, node[yNode].lNode, k);
        else return Query(node[xNode].rNode, node[yNode].rNode, k - dif);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int minA = inf;
    int maxA = -inf;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        minA = std::min(minA, a[i]);
        maxA = std::max(maxA, a[i]);
    }
    PresidentTree::Build(PresidentTree::root[0], minA, maxA);
    for (int i = 1; i <= n; i++) {
        PresidentTree::root[i] = PresidentTree::root[i - 1];
        PresidentTree::Modify(PresidentTree::root[i], a[i]);
    }
    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", PresidentTree::Query(PresidentTree::root[l - 1], PresidentTree::root[r], k));
    }
    return 0;
}