#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;

const int maxN = 5e5;
const int maxM = 5e5;
const int maxA = 1e5;
const int sqrN = 708;
const int sqrA = 317;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
lxl f[maxN + 10];
lxl g[maxN + 10];
int l, r;

struct Query1 {
    int i;
    int l, r;

    bool operator<(const Query1 &other) const {
        if (b[l] != b[other.l]) return l < other.l;
        return r < other.r;
    }
} query[maxM + 10];

struct Query2 {
    int i;
    int l, r;
    int k;
};

std::vector<Query2> querys[maxN + 10];

struct SegmentTree {
    struct Node {
        lxl val;
        lxl tag;
    } node[4 * maxA + 10];

    void MakeTag(int u, int l, int r, lxl val) {
        node[u].val += val * (r - l + 1);
        node[u].tag += val;
        return;
    }

    void PushDown(int u, int l, int r) {
        if (!node[u].tag) return;
        int mid = (l + r) / 2;
        MakeTag(2 * u, l, mid, node[u].tag);
        MakeTag(2 * u + 1, mid + 1, r, node[u].tag);
        node[u].tag = 0;
        return;
    }

    void PushUp(int u) {
        node[u].val = node[2 * u].val + node[2 * u + 1].val;
        return;
    }

    void Add(int u, int l, int r, int s, int t, lxl val) {
        if (s > t) return;
        if (s <= l && r <= t) {
            MakeTag(u, l, r, val);
            return;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, val);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
        PushUp(u);
        return;
    }

    lxl Ask(int u, int l, int r, int s, int t) {
        if (s > t) return 0;
        if (s <= l && r <= t) {
            return node[u].val;
        }
        PushDown(u, l, r);
        int mid = (l + r) / 2;
        if (t <= mid) return Ask(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
        return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
    }
} sum, cnt;

lxl ans[maxM + 10];

struct BlockArray {
    struct Block {
        lxl tag;
    } block[sqrA + 10];

    struct Array {
        lxl val;
    } array[maxA + 10];

    void Add(int pos, lxl val) {
        for (int i = (pos - 1) / sqrA + 1 + 1; i <= (maxA - 1) / sqrA + 1; i++) {
            block[i].tag += val;
        }
        for (int i = pos; i <= std::min(((pos - 1) / sqrA + 1) * sqrA, maxA); i++) {
            array[i].val += val;
        }
        return;
    }

    lxl Ask(int pos) {
        return array[pos].val + block[(pos - 1) / sqrA + 1].tag;
    }
} slf, slg;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> l >> r;
        query[i] = (Query1) {i, l, r};
    }
    std::sort(query + 1, query + m + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = sum.Ask(1, 1, maxA, a[i] + 1, maxA);
        g[i] = cnt.Ask(1, 1, maxA, 1, a[i] - 1);
        sum.Add(1, 1, maxA, a[i], a[i], a[i]);
        cnt.Add(1, 1, maxA, a[i], a[i], 1);
    }
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        if (l > query[i].l) {
            querys[r].push_back((Query2) {query[i].i, query[i].l, l - 1, 1});
            while (l > query[i].l) {
                l--;
                ans[query[i].i] -= f[l] + (g[l] - 1) * a[l];
            }
        }
        if (r < query[i].r) {
            querys[l - 1].push_back((Query2) {query[i].i, r + 1, query[i].r, -1});
            while (r < query[i].r) {
                r++;
                ans[query[i].i] += f[r] + (g[r] + 1) * a[r];
            }
        }
        if (l < query[i].l) {
            querys[r].push_back((Query2) {query[i].i, l, query[i].l - 1, -1});
            while (l < query[i].l) {
                ans[query[i].i] += f[l] + (g[l] - 1) * a[l];
                l++;
            }
        }
        if (r > query[i].r) {
            querys[l - 1].push_back((Query2) {query[i].i, query[i].r + 1, r, 1});
            while (r > query[i].r) {
                ans[query[i].i] -= f[r] + (g[r] + 1) * a[r];
                r--;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        slf.Add(a[i], a[i]);
        slg.Add(a[i], 1);
        for (auto query : querys[i]) {
            for (int j = query.l; j <= query.r; j++) {
                ans[query.i] += query.k * (slf.Ask(maxA) - slf.Ask(a[j]) + slg.Ask(a[j] - 1) * a[j]);
            }
        }
    }
    for (int i = 1; i <= m; i++) ans[query[i].i] += ans[query[i - 1].i];
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}