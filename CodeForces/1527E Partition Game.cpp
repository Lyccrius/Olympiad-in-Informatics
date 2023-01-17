#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int inf = 1e9;

const int maxN = 3.5e4;
const int maxK = 100;

int n, k;
int a[maxN + 10];
std::vector<int> appear[maxN + 10];
int last[maxN + 10];
lxl dp[maxK + 10][maxN + 10];

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        lxl val;
        lxl tag;
    } node[maxN << 2];

    void Mark(int xNode, int val) {
        node[xNode].val += val;
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

    void PushUp(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[xNode].val = std::min(node[lNode].val, node[rNode].val);
        return;
    }

    void Build(int xNode, int l, int r, int ver) {
        node[xNode].l = l;
        node[xNode].r = r;
        node[xNode].tag = 0;
        if (l == r) {
            node[xNode].val = dp[ver][l];
            return;
        }
        int mid = (l + r) / 2;
        node[xNode].lNode = 2 * xNode;
        node[xNode].rNode = 2 * xNode + 1;
        Build(node[xNode].lNode, l, mid, ver);
        Build(node[xNode].rNode, mid + 1, r, ver);
        PushUp(xNode);
        return;
    }

    void Modify(int xNode, int l, int r, int val) {
        if (l > node[xNode].r || node[xNode].l > r) return;
        if (l <= node[xNode].l && node[xNode].r <= r) {
            Mark(xNode, val);
            return;
        }
        PushDown(xNode);
        Modify(node[xNode].lNode, l, r, val);
        Modify(node[xNode].rNode, l, r, val);
        PushUp(xNode);
        return;
    }

    lxl Query(int xNode, int l, int r) {
        if (l > node[xNode].r || node[xNode].l > r) return inf;
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].val;
        PushDown(xNode);
        return std::min(Query(node[xNode].lNode, l, r), Query(node[xNode].rNode, l, r));
    }
} SGT;

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) appear[a[i]].push_back(i);
    for (int i = 1; i <= n; i++) for (int j = 0; j < appear[i].size(); j++) if (j == 0) last[appear[i][j]] = 0; else last[appear[i][j]] = appear[i][j - 1];
    for (int i = 1; i <= n; i++) dp[0][i] = inf; dp[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        SGT.Build(1, 0, n, i - 1);
        for (int j = 1; j <= n; j++) {
            if (last[j] != 0) SGT.Modify(1, 0, last[j] - 1, j - last[j]);
            dp[i][j] = SGT.Query(1, 0, j - 1);
        }
    }
    std::cout << dp[k][n] << '\n';
    return 0;
}