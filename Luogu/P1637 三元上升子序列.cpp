#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 3e4;

int n;
int a[maxN + 10];
std::vector<int> raw;
lxl ans;

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Modify(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Modify(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Modify(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s > t) return 0;
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret += Query(u * 2, l, mid, s, t);
        if (t >= mid + 1) ret += Query(u * 2 + 1, mid + 1, r, s, t);
        return ret;
    }
} SGT1, SGT2;

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i], raw.push_back(a[i]);
    std::sort(raw.begin(), raw.end());
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
    for (int i = 1; i <= n; i++) SGT2.Modify(1, 1, n, a[i], 1);
    for (int i = 1; i <= n; i++) {
        ans += SGT1.Query(1, 1, n, 1, a[i] - 1) * SGT2.Query(1, 1, n, a[i] + 1, n);
        SGT1.Modify(1, 1, n, a[i], 1);
        SGT2.Modify(1, 1, n, a[i], - 1);
    }
    std::cout << ans;
    return 0;
}