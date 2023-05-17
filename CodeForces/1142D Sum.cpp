#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;
typedef long long lxl;

const int maxN = 3000;
const int maxK = 3000;
const int maxT = 1e6;

int n, k;
int t[maxN + 10];
lxl s[maxN + 10];
vic a[maxN + 10];
int x;
lxl f[maxK + 10];
lxl ans;

struct SegmentTree {
    struct Node {
        vic q;
    } node[4 * maxN + 10];

    void Modify(int u, int l, int r, int s, int t, int x) {
        if (s > t) return;
        if (s <= l && r <= t) {
            node[u].q.push_back(x);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, x);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, x);
        return;
    }

    void Solve(int u, int l, int r, lxl *g) {
        lxl f[maxK + 10];
        for (int i = 0; i <= k; i++) f[i] = g[i];
        for (auto i : node[u].q) for (int j = k; j >= t[i]; j--) f[j] = std::max(f[j], f[j - t[i]] + s[i]);
        if (l == r) {
            lxl part = 0;
            for (int i = 0; i <= std::min(t[l], k); i++) {
                ans = std::max(ans, part + f[k - i]);
                part += a[l][i];
            }
            return;
        }
        int mid = (l + r) / 2;
        Solve(2 * u, l, mid, f);
        Solve(2 * u + 1, mid + 1, r, f);
        return;
    }
} SGT;

int main() {
    promote();
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        std::cin >> t[i];
        for (int j = 1; j <= t[i]; j++) {
            std::cin >> x;
            a[i].push_back(x);
            s[i] += x;
        }
        SGT.Modify(1, 1, n, 1, i - 1, i);
        SGT.Modify(1, 1, n, i + 1, n, i);
    }
    SGT.Solve(1, 1, n, f);
    std::cout << ans << '\n';
    return 0;
}