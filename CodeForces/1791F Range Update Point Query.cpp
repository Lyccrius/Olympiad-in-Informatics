#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int t;

int n, q;
int a[maxN + 10];
int opt;
int l, r;
int x;

struct SegmentTree {
    int node[maxN * 4 + 10];
    int tag[maxN * 4 + 10];

    void Clear() {
        for (int i = 1; i <= 4 * n; i++) node[i] = 0;
        for (int i = 1; i <= 4 * n; i++) tag[i] = 0;
        return;
    }

    void PushDown(int u) {
        int l = u * 2;
        int r = u * 2 + 1;
        node[l] += node[u];
        node[r] += node[u];
        node[u] = 0;
        return;
    }

    void Add(int u, int l, int r, int s, int t, int val) {
        if (s <= l && r <= t) {
            node[u] += val;
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Add(u * 2, l, mid, s, t, val);
        if (t > mid) Add(u * 2 + 1, mid + 1, r, s, t, val);
        return;
    }

    int Ask(int u, int l, int r, int p) {
        if (l == r) return node[u];
        PushDown(u);
        int mid = (l + r) / 2;
        if (p <= mid) return Ask(u * 2, l, mid, p);
        else return Ask(u * 2 + 1, mid + 1, r, p);
    }
} SGT;

int popcount(int x) {
    int ret = 0;
    while (x) {
        ret += x % 10;
        x /= 10;
    }
    return ret;
}

void mian() {
    std::cin >> n >> q;
    SGT.Clear();
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= q; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> l >> r;
            SGT.Add(1, 1, n, l, r, 1);
        } else {
            std::cin >> x;
            int t = SGT.Ask(1, 1, n, x);
            if (t != 0) {
                for (int j = 1; j <= t; j++) {
                    a[x] = popcount(a[x]);
                    if (a[x] / 10 == 0) break;
                }
                SGT.Add(1, 1, n, x, x, -t);
            }
            std::cout << a[x] << '\n';
        }
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}