#include <iostream>
#include <string>

typedef double dbl;
typedef std::string str;

const int maxN = 1e5;
const int maxT = 5e4;
const int maxP = 100;
const int maxS = 1e5;
const dbl eps = 1e-9;
const str Query = "Query";
const str Project = "Project";

int n;
str op;
int t;
dbl s, p;
int m;

struct Segment {
    dbl k, b;
} segment[maxN + 10];

dbl calc(int i, int x) {
    return segment[i].b + segment[i].k * x;
}

struct SegmentTree {
    struct Node {
        int i;
    } node[4 * maxT + 10];

    void MakeTag(int u, int l, int r, int i) {
        int mid = (l + r) / 2;
        if (calc(i, mid) > calc(node[u].i, mid) + eps) std::swap(i, node[u].i);
        if (calc(i, l) > calc(node[u].i, l) + eps) MakeTag(2 * u, l, mid, i);
        if (calc(i, r) > calc(node[u].i, r) + eps) MakeTag(2 * u + 1, mid + 1, r, i);
        return;
    }

    void Modify(int u, int l, int r, int i) {
        MakeTag(u, l, r, i);
        return;
    }

    dbl Query(int u, int l, int r, int p) {
        if (l == r) return calc(node[u].i, p);
        int mid = (l + r) / 2;
        dbl ret = calc(node[u].i, p);
        if (p <= mid) ret = std::max(ret, Query(2 * u, l, mid, p));
        if (p >= mid + 1) ret = std::max(ret, Query(2 * u + 1, mid + 1, r, p));
        return ret;
    }
} SGT;

void query() {
    std::cin >> t;
    std::cout << (int) SGT.Query(1, 1, maxT, t) / 100 << '\n';
    return;
}

void project() {
    std::cin >> s >> p;
    m++;
    segment[m].k = p;
    segment[m].b = s - p;
    SGT.Modify(1, 1, maxT, m);
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> op;
        if (op == Query) query();
        if (op == Project) project();
    }
    return 0;
}