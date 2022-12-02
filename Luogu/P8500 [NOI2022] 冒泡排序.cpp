#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 1e6 + 10;
const int maxM = 1e6 + 10;
const int inf = 1e9 + 10;

int t;
int n, m;
int L[maxM], R[maxM], V[maxM];
int force[maxN];
int a[maxM];
int from;
int res;
bool ok;
long long ans;

struct DisjointSet {
    struct Node {
        int fa;
    } node[maxN];

    void Init() {
        for (int i = 1; i <= n + 1; i++) node[i].fa = i;
        return;
    } 

    int Find(int x) {
        if (x == node[x].fa) return x;
        return node[x].fa = Find(node[x].fa);
    }
} DS;

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN << 2];

    int lowbit(int x) {
        return x & -x;
    }

    void Init() {
        for (int i = 1; i <= m; i++) node[i].val = 0;
        return;
    }

    void Add(int x) {
        while (x) {
            node[x].val++;
            x -= lowbit(x);
        }
        return;
    }

    int Ask(int x) {
        int res = 0;
        while (x <= m) {
            res += node[x].val;
            x += lowbit(x);
        }
        return res;
    }
} BIT;

struct SegmentTree {
    struct Node {
        int tag;
        int val;
        int from;
        int l;
        int r;
        int lNode;
        int rNode;
    } node[maxN << 2];

    int cnt;
    int root;

    void Build(int &xNode, int l, int r) {
        cnt++;
        xNode = cnt;
        node[xNode].tag = 0;
        node[xNode].val = 0;
        node[xNode].from = l;
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) return;
        int mid = (l + r) / 2;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        return;
    }

    void PushUp(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        node[xNode].val = std::min(node[lNode].val, node[rNode].val);
        if (node[xNode].val == node[lNode].val) node[xNode].from = node[lNode].from;
        else node[xNode].from = node[rNode].from;
    }

    void PushDown(int xNode) {
        int lNode = node[xNode].lNode;
        int rNode = node[xNode].rNode;
        if (node[xNode].tag) {
            node[lNode].val += node[xNode].tag;
            node[rNode].val += node[xNode].tag;
            node[lNode].tag += node[xNode].tag;
            node[rNode].tag += node[xNode].tag;
            node[xNode].tag = 0;
        }
        return;
    }

    void Add(int xNode, int l, int r, int val) {
        if (node[xNode].l >= l && node[xNode].r <= r) {
            node[xNode].val += val;
            node[xNode].tag += val;
            return;
        }
        PushDown(xNode);
        int mid = (node[xNode].l + node[xNode].r) / 2;
        if (l <= mid) Add(node[xNode].lNode, l, r, val);
        if (r >= mid + 1) Add(node[xNode].rNode, l, r, val);
        PushUp(xNode);
        return;
    }
    
    int Ask(int xNode, int l, int r) {
        if (node[xNode].l >= l && node[xNode].r <= r) {
            if (node[xNode].val < res) res = node[xNode].val, from = node[xNode].from;
            return res;
        }
        PushDown(xNode);
        int mid = (node[xNode].l + node[xNode].r) / 2;
        if (l <= mid) res = Ask(node[xNode].lNode, l, r);
        if (r >= mid + 1) res = Ask(node[xNode].rNode, l, r);
        return res;
    }
} ST;

struct Range {
    int l, r;

    bool operator<(Range other) const {
        return l < other.l;
    }
};

std::vector<Range> range[maxM];

void Init() {
    int space[maxM];
    for (int i = 1; i <= m; i++) space[i] = V[i];
    std::sort(space + 1, space + m + 1);
    int tot = std::unique(space + 1, space + m + 1) - space - 1;
    for (int i = 1; i <= m; i++) V[i] = std::lower_bound(space + 1, space + tot + 1, V[i]) - space;
    for (int i = 1; i <= m; i++) range[i].clear();
    for (int i = 1; i <= m; i++) range[V[i]].push_back((Range){L[i], R[i]});
    for (int i = 1; i <= m; i++) std::sort(range[i].begin(), range[i].end());
    for (int i = 1; i <= n; i++) force[i] = 0;
    for (int i = 1; i <= n; i++) a[i] = 0;
    DS.Init();
    BIT.Init();
    ST.Build(ST.root, 0, m + 1);
    ok = true;
    ans = 0;
    return;
}

void mian() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &L[i], &R[i], &V[i]);
    Init();
    for (int i = m; i >= 1 && ok; i--) if (range[i].size()) {
        int last = n + 1;
        for (int j = range[i].size() - 1; j >= 0 && ok; j--) if (range[i][j].r < last) {
            int pos = DS.Find(range[i][j].l);
            force[pos] = i;
            last = pos;
            if (pos > range[i][j].r) ok = false;
        }
        for (int j = 0; j < range[i].size(); j++) {
            for (int k = DS.Find(range[i][j].l); k <= range[i][j].r; k = DS.Find(k)) {
                a[k] = i;
                DS.node[k].fa = k + 1;
            }
        }
    }
    if (!ok) {
        printf("-1\n");
        return;
    }
    for (int i = 1; i <= n; i++) if (force[i]) {
        ans += BIT.Ask(force[i] + 1);
        BIT.Add(force[i]);
        ST.Add(ST.root, force[i] + 1, m + 1, 1);
    }
    for (int i = 1; i <= n; i++) if (force[i]) {
        ST.Add(ST.root, force[i] + 1, m + 1, -1);
        ST.Add(ST.root, 0, force[i] - 1, 1);
    } else {
        res = inf;
        ans += ST.Ask(ST.root, a[i], m + 1);
        if (from) ST.Add(ST.root, 0, from - 1, 1);
    }
    printf("%lld\n", ans);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}