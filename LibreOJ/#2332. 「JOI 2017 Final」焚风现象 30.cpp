#include <iostream>

typedef long long lxl;

const int maxN = 2e5;
const int maxQ = 2e5;
const int maxS = 1e6;
const int maxT = 1e6;
const int maxA = 1e6;
const int maxX = 1e6;

int n, q, s, t;
int a[maxN + 10];
int l, r, x;

struct SegmentTree {
    struct Node {
        lxl l, r;
        lxl val;
        lxl tag;
    } node[4 * maxN + 10];

    void MakeTag(int u, int val) {
        node[u].l += val;
        node[u].r += val;
        node[u].tag += val;
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(2 * u, node[u].tag);
        MakeTag(2 * u + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].l = node[2 * u].l;
        node[u].r = node[2 * u + 1].r;
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        if (node[2 * u].r < node[2 * u + 1].l) node[u].val -= (node[2 * u + 1].l - node[2 * u].r) * s;//, printf("- %d\n", (node[2 * u + 1].l - node[2 * u].r));
        if (node[2 * u].r > node[2 * u + 1].l) node[u].val += (node[2 * u].r - node[2 * u + 1].l) * t;//, printf("+ %d\n", (node[2 * u].r - node[2 * u + 1].l));
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].l = a[l];
            node[u].r = a[r];
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            MakeTag(u, val);
            //printf("%d: [%d, %d], l = %d, r = %d, val = %d\n", u, l, r, node[u].l, node[u].r, node[u].val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        //    printf("%d: [%d, %d], l = %d, r = %d, val = %d\n", u, l, r, node[u].l, node[u].r, node[u].val);
        return;
    }

    lxl Ask(int u, int l, int r) {
        return node[u].val;
    }
} SGT;

int main() {
    std::cin >> n >> q >> s >> t;
    for (int i = 0; i <= n; i++) std::cin >> a[i];
    SGT.Build(1, 0, n);
    for (int i = 1; i <= q; i++) {
        std::cin >> l >> r >> x;
        SGT.Add(1, 0, n, l, r, x);
        std::cout << SGT.Ask(1, 0, n) << '\n';
    }
    return 0;
}