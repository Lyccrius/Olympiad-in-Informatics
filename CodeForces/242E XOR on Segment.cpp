#include <iostream>

const int maxN = 1e5;
const int maxM = 5e4;
const int maxA = 1e6;
const int maxX = 1e6;

int n;
int a[maxN + 10];
int m;
int t, l, r, x;

struct SegmentTree {
    struct Node {
        int val;
        int tag;
    } node[maxN * 4 + 10];

    void MakeTag(int u, int l, int r) {
        node[u].val = (r - l + 1) - node[u].val;
        node[u].tag ^= 1;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void PushDown(int u, int l, int r) {
        if (!node[u].tag) return;
        int mid = (l + r) / 2;
        MakeTag(u * 2, l, mid);
        MakeTag(u * 2 + 1, mid + 1, r);
        node[u].tag = 0;
        return;
    }

    void Build(int u, int l, int r, int p) {
        if (l == r) {
            node[u].val = (a[l] >> p) & 1;
            return;
        }
        int mid = (l + r) / 2;
        Build(u * 2, l, mid, p);
        Build(u * 2 + 1, mid + 1, r, p);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(u * 2, l, mid, s, t);
        if (t >= mid + 1) Modify(u * 2 + 1, mid + 1, r, s, t);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT[20];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 0; i < 20; i++) SGT[i].Build(1, 1, n, i);
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> t;
        if (t == 1) {
            std::cin >> l >> r;
            long long res = 0;
            for (int i = 0; i < 20; i++) res += (1ll * SGT[i].Query(1, 1, n, l, r) << i);
            std::cout << res << '\n';
        } else if (t == 2) {
            std::cin >> l >> r >> x;
            for (int i = 0; i < 20; i++) if (x & (1 << i)) SGT[i].Modify(1, 1, n, l, r);
        }
    }
    return 0;
}