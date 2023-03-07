#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;

const int maxN = 1e5;
const int inf = 1e9 + 10;

int n;
int x, y;

struct Point {
    int x;
    int y;

    bool operator<(const Point &other) const {
        if (x != other.x) return x > other.x;
        return y < other.y;
    }
} point[maxN + 10];

std::vector<int> raw;

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
        if (s <= l && r <= t) return node[u].val;
        int ret = 0;
        int mid = (l + r) / 2;
        if (s <= mid) ret += Query(u * 2, l, mid ,s, t);
        if (t >= mid + 1) ret += Query(u * 2 + 1, mid + 1, r, s, t);
        return ret;
    }
} SGT;

int l[maxN + 10];
int r[maxN + 10];
int s, t;
int ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> point[i].x >> point[i].y, raw.push_back(point[i].y);
    std::sort(point + 1, point + n + 1);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) point[i].y = std::lower_bound(raw.begin(), raw.end(), point[i].y) - raw.begin() + 1;
    for (int i = 1; i <= n; i++) l[i] = inf;
    for (int i = 1; i <= n; i++) r[i] = - inf;
    for (int i = 1; i <= n; i++) l[point[i].y] = std::min(l[point[i].y], point[i].x);
    for (int i = 1; i <= n; i++) r[point[i].y] = std::max(r[point[i].y], point[i].x);
    for (int i = 1, j; i <= n; i = j) {
        s = point[i].y;
        j = i;
        while (j <= n && point[j].x == point[i].x) {
            if (point[j].x == l[point[j].y]) SGT.Modify(1, 1, raw.size(), point[j].y, - 1);
            if (point[j].x == r[point[j].y]) SGT.Modify(1, 1, raw.size(), point[j].y, 1);
            t = point[j].y;
            j++;
        }
        ans += SGT.Query(1, 1, raw.size(), s, t);
    }
    std::cout << ans + raw.size();
    return 0;
}