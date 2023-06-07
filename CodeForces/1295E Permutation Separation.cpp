#include <iostream>
#include <map>

typedef std::map<int, int> mii;
typedef long long lxl;

const int maxN = 2e5;
const int maxA = 1e9;

int n;
int p[maxN + 10];
int a[maxN + 10];
lxl pre[maxN + 10];
lxl ans;
mii pos;

struct SegmentTree {
    struct Node {
        lxl val;
        lxl tag;
    } node[4 * maxN + 10];

    void MakeTag(int u, lxl val) {
        node[u].val += val;
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
        node[u].val = std::min(node[2 * u].val, node[2 * u + 1].val);
        return;
    }

    void Add(int u, int l, int r, int s, int t, lxl val) {
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, val);
            return;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    lxl Ask(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        PushDown(u);
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return std::min(Ask(2 * u, l, mid, s, t), Ask(2 * u + 1, mid + 1, r, s, t));
    }
} SGT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
    for (int i = 1; i <= n; i++) SGT.Add(1, 1, n, i, i, pre[i]);
    for (int i = 1; i <= n; i++) pos[p[i]] = i;
    ans = SGT.Ask(1, 1, n, 1, n - 1);
    for (int i = 1; i <= n; i++) {
        SGT.Add(1, 1, n, 1, pos[i] - 1, a[pos[i]]);
        SGT.Add(1, 1, n, pos[i], n - 1, - a[pos[i]]);
        ans = std::min(ans, SGT.Ask(1, 1, n, 1, n - 1));
    }
    std::cout << ans << '\n';
    return 0;
}