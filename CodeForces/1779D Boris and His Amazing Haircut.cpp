#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 2e5;
const int maxM = 2e5;

int t;

int n;
int a[maxN + 10];
int b[maxN + 10];
int m;
int x[maxM + 10];

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        int tag;
        int val;
    } node[maxN << 2];

    int cnt;
    int root;

    void Clear() {
        for (int i = 1; i <= (n << 2); i++) {
            node[i].l = 0;
            node[i].r = 0;
            node[i].lNode = 0;
            node[i].rNode = 0;
            node[i].val = 0;
            node[i].tag = 0;
        }
        return;
    }

    void Clone(int &xNode) {
        cnt++;
        node[cnt] = node[xNode];
        xNode = cnt;
        return;
    }

    void PushUp(int xNode) {
        node[xNode].val = std::max(node[node[xNode].lNode].val, node[node[xNode].rNode].val);
        return;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[lNode].val = std::min(node[lNode].val, node[xNode].tag);
        node[rNode].val = std::min(node[rNode].val, node[xNode].tag);
        node[lNode].tag = node[xNode].tag;
        node[rNode].tag = node[xNode].tag;
        node[xNode].tag = 0;
        return;
    }

    void Build(int &xNode, int l, int r) {
        Clone(xNode);
        node[xNode].l = l;
        node[xNode].r = r;
        if (node[xNode].l == node[xNode].r) {
            node[xNode].val = b[node[xNode].l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        PushUp(xNode);
        return;
    }

    int Query(int xNode, int l, int r) {
        if (l <= node[xNode].l && node[xNode].r <= r) return node[xNode].val;
        int mid = (node[xNode].l + node[xNode].r) >> 1;
        int ret = 0;
        if (l <= mid) ret = std::max(ret, Query(node[xNode].lNode, l, r));
        if (r >= mid + 1) ret = std::max(ret, Query(node[xNode].rNode, l, r));
        return ret;
    }

    void Modify(int xNode, int l, int r, int val) {
        if (node[xNode].l == node[xNode].r) {
            node[xNode].val = std::min(node[xNode].val, val);
            return;
        }
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].val = std::min(node[xNode].val, val);
            node[xNode].tag = val;
            return;
        }
        if (node[xNode].val) PushDown(xNode);
        Modify(node[xNode].lNode, l, r, val);
        Modify(node[xNode].rNode, l, r, val);
        PushUp(xNode);
        return;
    }
} SGT;

std::vector<int> appear[maxM + 10];

void Init() {
    for (int i = 1; i <= m; i++) appear[i].clear();
    SGT.Clear();
    return;
}

bool check(int p, int cnt) {
    for (int i = 1; i < appear[p].size(); i++) if (SGT.Query(SGT.root, appear[p][i - 1], appear[p][i]) > x[p]) cnt--;
    return cnt >= 1;
}

void mian() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) scanf("%d", &x[i]);
    Init();
    std::sort(x + 1, x + m + 1);
    bool ok = true;
    for (int i = 1; i <= n; i++) if (a[i] < b[i]) { ok = false; break; }
    for (int i = 1; i <= n; i++) if (a[i] > b[i]) {
        int p = std::lower_bound(x + 1, x + m + 1, b[i]) - x;
        if (x[p] != b[i] || p > m) { ok = false; break; }
        appear[p].push_back(i);
    }
    if (ok == false) {
        printf("NO\n");
        return;
    }
    SGT.Build(SGT.root, 1, n);
    int cnt = 1;
    for (int i = m; i >= 1; i--) {
        if (x[i] == x[i - 1]) cnt++;
        else ok &= check(i, cnt), cnt = 1;
    }
    if (ok == false) printf("NO\n");
    else printf("YES\n");
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}