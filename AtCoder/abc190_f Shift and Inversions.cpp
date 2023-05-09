#include <iostream>

typedef long long lxl;

const int maxN = 3e5;

int n;
int a[maxN + 10];
lxl res = 0;

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * maxN + 10];

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        return;
    }

    void Add(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(2 * u, l, mid, pos, val);
        if (pos >= mid + 1) Add(2 * u + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Ask(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) {
        res += SGT.Ask(1, 0, n, a[i], n);
        SGT.Add(1, 0, n, a[i], 1);
    }
    for (int i = 1; i <= n; i++) {
        std::cout << res << '\n';
        res += n - a[i] - a[i] - 1;
    }
    return 0;
}