#include <iostream>
#include <algorithm>
#include <vector>

typedef double dbl;
typedef std::vector<dbl> vbc;

const int maxN = 2e3;
const int maxA = 1e4;

int n, a;
int w[maxN + 10], x[maxN + 10], t[maxN + 10];
dbl l[maxN + 10], r[maxN + 10];
vbc raw;
int ans;

struct SegmentTree {
    struct Node {
        int val;
        int tag;
    } node[4 * 2 * maxN + 10];

    void Clear() {
        for (int i = 1; i <= 4 * 2 * n; i++) {
            node[i].val = 0;
            node[i].tag = 0;
        }
        return;
    }

    void MakeTag(int u, int val) {
        node[u].val += val;
        node[u].tag += val;
        return;
    }

    void PushUp(int u) {
        node[u].val = std::max(node[2 * u].val, node[2 * u + 1].val);
        return;
    }

    void PushDown(int u) {
        if (!node[u].tag) return;
        MakeTag(2 * u, node[u].tag);
        MakeTag(2 * u + 1, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void Add(int u, int l, int r, int s, int t, int val) {
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

    int Ask(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        PushDown(u);
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return std::max(Ask(2 * u, l, mid, s, t), Ask(2 * u + 1, mid + 1, r, s, t));
    }
} SGT;

int solve(int p) {
    raw.clear();
    SGT.Clear();
    for (int i = 1; i <= n; i++) {
        if (x[p] <= x[i] && x[i] <= x[p] + a) {
            l[i] = 0;
        } else if (x[i] < x[p]) {
            if (t[i] == t[p]) {
                l[i] = maxA + 10;
            } else if (t[i] < t[p]) {
                l[i] = maxA + 10;
            } else if (t[i] > t[p]) {
                l[i] = 1.0 * (x[p] - x[i]) / (t[i] - t[p]);
            }
        } else if (x[i] > x[p] + a) {
            if (t[i] == t[p]) {
                l[i] = maxA + 10;
            } else if (t[i] < t[p]) {
                l[i] = 1.0 * (x[i] - (x[p] + a)) / (t[p] - t[i]);
            } else if (t[i] > t[p]) {
                l[i] = maxA + 10;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (x[p] <= x[i] && x[i] <= x[p] + a) {
            if (t[i] == t[p]) {
                r[i] = maxA + 10;
            } else if (t[i] < t[p]) {
                r[i] = 1.0 * (x[i] - x[p]) / (t[p] - t[i]);
            } else if (t[i] > t[p]) {
                r[i] = 1.0 * (x[p] + a - x[i]) / (t[i] - t[p]);
            }
        } else if (x[i] < x[p]) {
            if (t[i] == t[p]) {
                r[i] = 0;
            } else if (t[i] < t[p]) {
                r[i] = 0;
            } else if (t[i] > t[p]) {
                r[i] = 1.0 * (x[p] + a - x[i]) / (t[i] - t[p]);
            }
        } else if (x[i] > x[p] + a) {
            if (t[i] == t[p]) {
                r[i] = 0;
            } else if (t[i] < t[p]) {
                r[i] = 1.0 * (x[i] - x[p]) / (t[p] - t[i]);
            } else if (t[i] > t[p]) {
                r[i] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        raw.push_back(l[i]);
        raw.push_back(r[i]);
    }
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) {
        l[i] = std::lower_bound(raw.begin(), raw.end(), l[i]) - raw.begin();
        r[i] = std::lower_bound(raw.begin(), raw.end(), r[i]) - raw.begin();
        SGT.Add(1, 0, raw.size(), l[i], r[i], w[i]);
    }
    int t = std::lower_bound(raw.begin(), raw.end(), 0) - raw.begin();
    return SGT.Ask(1, 0, raw.size(), t, raw.size());
}

int main() {
    std::cin >> n >> a;
    for (int i = 1; i <= n; i++) std::cin >> w[i] >> x[i] >> t[i];
    for (int i = 1; i <= n; i++) ans = std::max(ans, solve(i));
    std::cout << ans << '\n';
    return 0;
}