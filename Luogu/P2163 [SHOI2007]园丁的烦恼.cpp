#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

const int maxN = 5e5;
const int maxM = 5e5;

int n, m;
int x[maxN + 10], y[maxN + 10];
int a[maxM + 10], b[maxM + 10], c[maxM + 10], d[maxM + 10];

struct Point {
    int i;
    int x;
    int y;

    bool operator<(const Point &other) const {
        return x < other.x;
    }
};

struct Query {
    int i;
    int x;
    int l, r;
    int k;

    bool operator<(const Query &other) const {
        return x < other.x;
    }
};

std::deque<Point> points;
std::deque<Query> querys;
std::vector<int> rawX;
std::vector<int> rawY;

int ans[maxM + 10];

struct SegmentTree {
    struct Node {
        int val;
    } node[maxN * 4 + 10];

    void PushUp(int u) {
        node[u].val = node[u * 2].val + node[u * 2 + 1].val;
        return;
    }

    void Add(int u, int l, int r, int pos, int val) {
        if (l == r) {
            node[u].val += val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) Add(u * 2, l, mid, pos, val);
        if (pos >= mid + 1) Add(u * 2 + 1, mid + 1, r, pos, val);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) return node[u].val;
        int mid = (l + r) / 2;
        if (t <= mid) return Query(u * 2, l, mid, s, t);
        if (s >= mid + 1) return Query(u * 2 + 1, mid + 1, r, s, t);
        return Query(u * 2, l, mid, s, t) + Query(u * 2 + 1, mid + 1, r, s, t);
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i] >> y[i];
        rawX.push_back(x[i]);
        rawY.push_back(y[i]);
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i] >> b[i] >> c[i] >> d[i]; a[i]--;
        rawX.push_back(a[i]);
        rawX.push_back(c[i]);
        rawY.push_back(b[i]);
        rawY.push_back(d[i]);
    }
    std::sort(rawX.begin(), rawX.end());
    std::sort(rawY.begin(), rawY.end());
    rawX.erase(std::unique(rawX.begin(), rawX.end()), rawX.end());
    rawY.erase(std::unique(rawY.begin(), rawY.end()), rawY.end());
    for (int i = 1; i <= n; i++) x[i] = std::lower_bound(rawX.begin(), rawX.end(), x[i]) - rawX.begin() + 1;
    for (int i = 1; i <= n; i++) y[i] = std::lower_bound(rawY.begin(), rawY.end(), y[i]) - rawY.begin() + 1;
    for (int i = 1; i <= m; i++) a[i] = std::lower_bound(rawX.begin(), rawX.end(), a[i]) - rawX.begin() + 1;
    for (int i = 1; i <= m; i++) c[i] = std::lower_bound(rawX.begin(), rawX.end(), c[i]) - rawX.begin() + 1;
    for (int i = 1; i <= m; i++) b[i] = std::lower_bound(rawY.begin(), rawY.end(), b[i]) - rawY.begin() + 1;
    for (int i = 1; i <= m; i++) d[i] = std::lower_bound(rawY.begin(), rawY.end(), d[i]) - rawY.begin() + 1;
    for (int i = 1; i <= n; i++) points.push_back((Point) {i, x[i], y[i]});
    for (int i = 1; i <= m; i++) querys.push_back((Query) {i, a[i], b[i], d[i], - 1});
    for (int i = 1; i <= m; i++) querys.push_back((Query) {i, c[i], b[i], d[i], 1});
    std::sort(points.begin(), points.end());
    std::sort(querys.begin(), querys.end());
    for (auto query : querys) {
        while (points.size() && points.front().x <= query.x) {
            SGT.Add(1, 0, rawY.size(), points.front().y, 1);
            points.pop_front();
        }
        ans[query.i] += query.k * SGT.Query(1, 0, rawY.size(), query.l, query.r);
    }
    for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
    return 0;
}