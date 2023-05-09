#include <iostream>
#include <algorithm>
#include <deque>

const int maxN = 2e6;
const int maxC = 2e6;
const int maxM = 2e6;

int n, c, m;
int x[maxN + 10];
int l, r;
int pre1[maxC + 10];
int pre2[maxC + 10];
int ans[maxM + 10];

struct Query {
    int i;
    int l, r;

    bool operator<(Query other) const {
        return r < other.r;
    }
};
std::deque<Query> querys;

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
    std::cin >> n >> c >> m;
    for (int i = 1; i <= n; i++) std::cin >> x[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        querys.push_back((Query) {i, l, r});
    }
    std::sort(querys.begin(), querys.end());
    for (int i = 1; i <= n; i++) {
        if (!pre2[x[i]]) {
            pre2[x[i]] = i;
        } else if (!pre1[x[i]]) {
            SGT.Add(1, 0, n, pre2[x[i]], 1);
            pre1[x[i]] = i;
        } else {
            SGT.Add(1, 0, n, pre2[x[i]], -1);
            SGT.Add(1, 0, n, pre1[x[i]], 1);
            pre2[x[i]] = pre1[x[i]];
            pre1[x[i]] = i;
        }
        while (querys.size() && querys.front().r <= i) {
            ans[querys.front().i] = SGT.Ask(1, 0, n, querys.front().l, querys.front().r);
            querys.pop_front();
        }
    }
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}