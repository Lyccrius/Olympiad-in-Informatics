#include <cstdio>
#include <algorithm>

const int maxn = 1e6 + 10;
const int root = 1;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        long long tag;
        long long val;
    };

    int array[maxn];
    Node node[maxn << 1];

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[lNode].tag += node[xNode].tag;
        node[rNode].tag += node[xNode].tag;
        node[lNode].val -= node[xNode].tag;
        node[rNode].val -= node[xNode].tag;
        node[xNode].tag = 0;
        return;
    }

    void PushUp(int xNode) {
        node[xNode].val = std::min(node[node[xNode].lNode].val, node[node[xNode].rNode].val);
        return;
    }
    
    void Build(int l, int r, int xNode) {
        node[xNode].l = l;
        node[xNode].r = r;

        if (l == r) {
            node[xNode].val = array[l];
            return;
        }

        int mid = (l + r) / 2;
        node[xNode].lNode = xNode * 2;
        node[xNode].rNode = xNode * 2 + 1;
        Build(l, mid, node[xNode].lNode);
        Build(mid + 1, r, node[xNode].rNode);
        PushUp(xNode);
        return;
    }

    void Modify(int l, int r, int xNode, int xVal) {
        if (node[xNode].l >= l &&
            node[xNode].r <= r) {
            node[xNode].tag += xVal;
            node[xNode].val -= xVal;
            return;
        }

        if (node[xNode].tag && 
            node[xNode].l != node[xNode].r) PushDown(xNode);
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        if (l <= node[lNode].r) Modify(l, r, lNode, xVal);
        if (r >= node[rNode].l) Modify(l, r, rNode, xVal);
        PushUp(xNode);
        return;
    }
};

int n, m;
int *r;
int d, s, t;

SegmentTree ClassRoom;

int main() {
    scanf("%d%d", &n, &m);
    r = &ClassRoom.array[0];
    for (int i = 1; i <= n; i++) scanf("%d", &r[i]);
    ClassRoom.Build(1, n, root);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &d, &s, &t);
        ClassRoom.Modify(s, t, root, d);
        if (ClassRoom.node[root].val < 0) {
            printf("-1\n");
            printf("%d\n", i);
            return 0;
        }
    }
    printf("0");
    return 0;
}