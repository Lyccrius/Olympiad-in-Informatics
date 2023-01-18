#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int inf = 1e9;
const int maxN = 1e5;
const int maxM = 1e5;
const int logA = 30;

int n;
int a[maxN + 10];
int m;
int l, r;
int res;
int ans;
int lst;

struct SegmentTree {
    struct Node {
        int l, r;
        int lson;
        int rson;
        int val;
    } node[maxN * 4 + maxN * logA + 10];

    int ncnt;

    int root[maxN + 10];

    void Build(int &u, int l, int r) {
        u = ++ncnt;
        node[u].l = l;
        node[u].r = r;
        return;
    }

    void Clone(int &u, int v) {
        ++ncnt;
        node[ncnt] = node[v];
        u = ncnt;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[node[u].lson].val + node[node[u].rson].val;
        return;
    }

    void Modify(int &u, int p) {
        if (p <= node[u].l && node[u].r <= p) {
            node[u].val += p;
            return;
        }
        int mid = (node[u].l + node[u].r) / 2;
        if (p <= mid) {
            if (node[u].lson == 0) Build(node[u].lson, node[u].l, mid);
            else Clone(node[u].lson, node[u].lson);
            Modify(node[u].lson, p);
        } else {
            if (node[u].rson == 0) Build(node[u].rson, mid + 1, node[u].r);
            else Clone(node[u].rson, node[u].rson);
            Modify(node[u].rson, p);
        }
        PushUp(u);
        return;
    }

    int Query(int u, int v, int l, int r) {
        if (l <= node[v].l && node[v].r <= r) return node[v].val - node[u].val;
        int mid = (node[v].l + node[v].r) / 2;
        int ret = 0;
        if (l <= mid) {
            //if (node[u].lson == 0) Build(node[u].lson, node[u].l, mid);
            //if (node[v].lson == 0) Build(node[v].lson, node[v].l, mid);
            if (node[v].lson != 0) ret += Query(node[u].lson, node[v].lson, l, r);
        }
        if (r > mid) {
            //if (node[u].rson == 0) Build(node[u].rson, mid + 1, node[u].r);
            //if (node[v].rson == 0) Build(node[v].rson, mid + 1, node[v].r);
            if (node[v].rson != 0) ret += Query(node[u].rson, node[v].rson, l, r);
        }
        //printf("[%d, %d] on [%d, %d] = %d\n", l, r, node[v].l, node[v].r, ret);
        return ret;
    }
} SGT;

int main() {
    SGT.Build(SGT.root[0], 1, inf);
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) SGT.Clone(SGT.root[i], SGT.root[i - 1]), SGT.Modify(SGT.root[i], a[i]);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        ans = 1;
        lst = 0;
        while (true) {
            res = SGT.Query(SGT.root[l - 1], SGT.root[r], lst + 1, ans);
            lst = ans;
            if (res) ans = ans + res;
            else break;
        }
        std::cout << ans << '\n';
    }
    return 0;
}