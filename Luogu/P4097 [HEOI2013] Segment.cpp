#include <iostream>

typedef double dbl;
typedef std::pair<dbl, int> pdi;

const int maxN = 1e5;
const int maxX = 39989;
const int maxY = 1e9;
const dbl eps = 1e-9;

int n;
int op;
int k;
int x_0, y_0, x_1, y_1;
int lastans;

int m;
struct Segment {
    dbl k, b;
} segment[maxN + 10];

dbl f(int i, int x) {
    return segment[i].b + segment[i].k * x;
}

pdi max(pdi x, pdi y) {
    if (std::abs(x.first - y.first) >= eps) {
        if (x.first > y.first) return x;
        if (x.first < y.first) return y;
    } else {
        if (x.second < y.second) return x;
        if (x.second > y.second) return y;
    }
}

struct SegmentTree {
    struct Node {
        int s;
    } node[4 * maxX + 10];

    void MakeTag(int u, int l, int r, int s) {
        int mid = (l + r) / 2;
        if (f(s, mid) > f(node[u].s, mid) + eps) std::swap(node[u].s, s);
        int lg = (f(s, l) >= f(node[u].s, l) + eps);
        int rg = (f(s, r) >= f(node[u].s, r) + eps);
        int le = (std::abs(f(s, l) - f(node[u].s, l)) < eps);
        int re = (std::abs(f(s, r) - f(node[u].s, r)) < eps);
        if (lg || (le && s < node[u].s)) MakeTag(2 * u, l, mid, s);
        if (rg || (re && s < node[u].s)) MakeTag(2 * u + 1, mid + 1, r, s);
        return;
    }

    void Add(int u, int l, int r, int s, int t, int i) {
        if (s <= l && r <= t) {
            MakeTag(u, l, r, i);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Add(2 * u, l, mid, s, t, i);
        if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, i);
        return;
    }

    pdi Ask(int u, int l, int r, int x) {
        if (x < l || r < x) return std::make_pair(0.0, 0);
        if (l == r) return std::make_pair(f(node[u].s, x), node[u].s);
        int mid = (l + r) / 2;
        pdi ret = std::make_pair(f(node[u].s, x), node[u].s);
        ret = max(ret, Ask(2 * u, l, mid, x));
        ret = max(ret, Ask(2 * u + 1, mid + 1, r, x));
        return ret;
    }
} SGT;

void ask() {
    k = (k + lastans - 1) % maxX + 1;
    std::cout << (lastans = SGT.Ask(1, 1, maxX, k).second) << '\n';
    return;
}

void add() {
    x_0 = (x_0 + lastans - 1) % maxX + 1;
    y_0 = (y_0 + lastans - 1) % maxY + 1;
    x_1 = (x_1 + lastans - 1) % maxX + 1;
    y_1 = (y_1 + lastans - 1) % maxY + 1;
    m++;
    if (x_0 == x_1) segment[m].k = 0, segment[m].b = std::max(y_0, y_1);
    else segment[m].k = 1.0 * (y_1 - y_0) / (x_1 - x_0), segment[m].b = y_0 - segment[m].k * x_0;
    if (x_0 > x_1) std::swap(x_0, x_1), std::swap(y_0, y_1);
    SGT.Add(1, 1, maxX, x_0, x_1, m);
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> op;
        if (op == 0) std::cin >> k, ask();
        if (op == 1) std::cin >> x_0 >> y_0 >> x_1 >> y_1, add();
    }
    return 0;
}