#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

const int maxH = 2e5;
const int maxW = 2e5;
const int maxM = 2e5;

int h, w, m;
int x, y;
int r[maxH + 10];
int c[maxW + 10];
vic t[maxW + 10];
lxl ans;

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * maxH + 10];

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
    std::cin >> h >> w >> m;
    for (int i = 1; i <= h; i++) r[i] = w + 1;
    for (int i = 1; i <= w; i++) c[i] = h + 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        r[x] = std::min(r[x], y);
        c[y] = std::min(c[y], x);
    }
    bool flag = true;
    for (int i = 1; i <= h; i++) {
        if (flag) {
            ans += r[i] - 1;
            if (r[i] <= w) t[r[i] + 1].push_back(i);
            if (r[i] == 1) flag = false;
        } else {
            t[2].push_back(i);
        }
    }
    for (int i = 1; i <= w; i++) {
        if (c[i] == 1) break;
        for (auto j : t[i]) SGT.Add(1, 1, h, j, 1);
        ans += SGT.Ask(1, 1, h, 1, c[i] - 1);
    }
    std::cout << ans << '\n';
    return 0;
}