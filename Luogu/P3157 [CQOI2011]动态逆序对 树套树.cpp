#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 5e4;
const int logN = 17;

int n, m;
int a[maxN + 10];
int b[maxM + 10];
int c[maxN + 10];

struct Node {
    int p;
    int v;
    int t;

    bool operator<(const Node &other) const {
        return t > other.t;
    }
} node[maxN + 10];

struct BinaryIndexedTree {
    struct SegmentTree {
        struct Node {
            int lson;
            int rson;
            int val;
        } node[maxN * logN * logN + 10];

        int ncnt;
        int root[maxN + 10];

        void PushUp(int u) {
            node[u].val = node[node[u].lson].val + node[node[u].rson].val;
            return;
        }

        void Add(int &u, int l, int r, int v) {
            if (!u) u = ++ncnt;
            if (l == r) {
                node[u].val += 1;
                return;
            }
            int mid = (l + r) / 2;
            if (v <= mid) Add(node[u].lson, l, mid, v);
            if (v >= mid + 1) Add(node[u].rson, mid + 1, r, v);
            PushUp(u);
            return;
        }

        int Ask(int &u, int l, int r, int s, int t) {
            if (!u) return 0;
            if (s <= l && r <= t) return node[u].val;
            int mid = (l + r) / 2;
            if (t <= mid) return Ask(node[u].lson, l, mid, s, t);
            if (s >= mid + 1) return Ask(node[u].rson, mid + 1, r, s, t);
            return Ask(node[u].lson, l, mid, s, t) + Ask(node[u].rson, mid + 1, r, s, t);
        }
    } SGT;

    int lowbit(int x) {
        return x & - x;
    }

    void Add(int p, int v) {
        while (p <= n) {
            SGT.Add(SGT.root[p], 1, n, v);
            p += lowbit(p);
        }
        return;
    }

    lxl Ask(int p, int s, int t) {
        lxl ret = 0;
        while (p >= 1) {
            ret += SGT.Ask(SGT.root[p], 1, n, s, t);
            p -= lowbit(p);
        }
        return ret;
    }
} BIT;

lxl ans[maxM + 10];

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) c[a[i]] = i;
    for (int i = 1; i <= n; i++) node[i].p = i;
    for (int i = 1; i <= n; i++) node[i].v = a[i];
    for (int i = 1; i <= m; i++) node[c[b[i]]].t = i;
    for (int i = 1; i <= n; i++) if (node[i].t == 0) node[i].t = m + 1;
    std::sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) {
        ans[node[i].t] += BIT.Ask(node[i].p, node[i].v, n);
        ans[node[i].t] += BIT.Ask(n, 1, node[i].v) - BIT.Ask(node[i].p, 1, node[i].v);
        BIT.Add(node[i].p, node[i].v);
    }
    for (int i = m; i >= 1; i--) ans[i] += ans[i + 1];
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}