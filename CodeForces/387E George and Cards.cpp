#include <iostream>
#include <algorithm>
#include <set>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::set<int> sit;
typedef long long lxl;

const int maxN = 1e6;
const int maxM = 1e6;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int c[maxN + 10];
int d[maxN + 10];
sit s;
lxl ans;

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
        if (s > t) return 0;
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) c[a[i]] = i;
    for (int i = 1; i <= n; i++) d[b[i]] = i;
    for (int i = 1; i <= n; i++) SGT.Add(1, 1, n, i, 1);
    for (int i = 1; i <= n; i++) {
        if (d[i]) {
            s.insert(c[i]);
        } else {
            int l = 1;
            int r = n;
            auto it = s.lower_bound(c[i]);
            if (it != s.end()) r = *it - 1;
            if (it != s.begin()) l = *(--it) + 1;
            ans += SGT.Ask(1, 1, n, l, r);
            SGT.Add(1, 1, n, c[i], -1);
        }
    }
    std::cout << ans << '\n';
    return 0;
}