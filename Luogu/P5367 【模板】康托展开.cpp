#include <iostream>

const int maxN = 1e6;
const int mod = 998244353;

int n;
int a[maxN + 10];
int f[maxN + 10];
int ans;

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
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

int main() {
    f[0] = 1;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) f[i] = 1ll * f[i - 1] * i % mod;
    for (int i = n; i >= 1; i--) {
        ans = (1ll * ans + 1ll * SGT.Ask(1, 1, n, 1, a[i]) * f[n - i] % mod) % mod;
        SGT.Add(1, 1, n, a[i], 1);
    }
    std::cout << ans + 1 << '\n';
    return 0;
}