#include <iostream>

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int op[maxM + 10], l[maxM + 10], r[maxM + 10];
int q;

struct SegmentTree {
    struct Node {
        int val;
        int tag;
        int tav;
    } node[4 * maxN + 10];

    void MakeTag(int u, int l, int r, int val) {
        node[u].val = val * (r - l + 1);
        node[u].tav = val;
        node[u].tag = true;
        return;
    }

    void PushDown(int u, int l, int r) {
        if (node[u].tag == false) return;
        int mid = (l + r) / 2;
        MakeTag(2 * u, l, mid, node[u].tav);
        MakeTag(2 * u + 1, mid + 1, r, node[u].tav);
        node[u].tag = false;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        node[u].tag = false;
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = b[l];
            node[u].tag = false;
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int val) {
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return Query(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
        return Query(2 * u, l, mid, s, t) + Query(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

bool check(int x) {
    for (int i = 1; i <= n; i++) if (a[i] >= x) b[i] = 1; else b[i] = 0;
    SGT.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        int sum = SGT.Query(1, 1, n, l[i], r[i]);
        if (op[i] == 0) {
            SGT.Modify(1, 1, n, l[i], r[i] - sum, 0);
            SGT.Modify(1, 1, n, r[i] - sum + 1, r[i], 1);
        } else {
            SGT.Modify(1, 1, n, l[i], l[i] + sum - 1, 1);
            SGT.Modify(1, 1, n, l[i] + sum, r[i], 0);
        }
    }
    return SGT.Query(1, 1, n, q, q);
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> op[i] >> l[i] >> r[i];
    std::cin >> q;
    int l = 1;
    int r = n;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    std::cout << l << '\n';
    return 0;
}