#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long lxl;
typedef double dbl;

const int maxN = 1e5;
const int maxK = 100;

int n, k;

struct Point {
    int x, y;
} p[maxN + 10];

bool cmpByX(Point a, Point b) {
    return a.x < b.x;
}

bool cmpByY(Point a, Point b) {
    return a.y < b.y;
}

std::priority_queue<lxl, std::vector<lxl>, std::greater<lxl> > q;

lxl square(lxl x) {
    return x * x;
}

struct KDTree {
    struct Node {
        int lson;
        int rson;
        int l, r;
        int d, u;
    } node[maxN + 10];

    lxl dis(int a, int b) {
        return std::max(square(p[a].x - node[b].l), square(p[a].x - node[b].r)) + std::max(square(p[a].y - node[b].d), square(p[a].y - node[b].u));
    }

    void PushUp(int u) {
        node[u].l = node[u].r = p[u].x;
        node[u].d = node[u].u = p[u].y;
        if (node[u].lson) {
            node[u].l = std::min(node[u].l, node[node[u].lson].l);
            node[u].r = std::max(node[u].r, node[node[u].lson].r);
            node[u].d = std::min(node[u].d, node[node[u].lson].d);
            node[u].u = std::max(node[u].u, node[node[u].lson].u);
        }
        if (node[u].rson) {
            node[u].l = std::min(node[u].l, node[node[u].rson].l);
            node[u].r = std::max(node[u].r, node[node[u].rson].r);
            node[u].d = std::min(node[u].d, node[node[u].rson].d);
            node[u].u = std::max(node[u].u, node[node[u].rson].u);
        }
        return;
    }

    int Build(int l, int r) {
        if (l > r) return 0;
        int mid = (l + r) / 2;
        dbl sx = 0, sy = 0;
        dbl ax = 0, ay = 0;
        dbl dx = 0, dy = 0;
        for (int i = l; i <= r; i++) sx += p[i].x;
        for (int i = l; i <= r; i++) sy += p[i].y;
        ax = sx / (r - l + 1);
        ay = sy / (r - l + 1);
        for (int i = l; i <= r; i++) dx += (ax - p[i].x) * (ax - p[i].x);
        for (int i = l; i <= r; i++) dy += (ay - p[i].y) * (ay - p[i].y);
        if (dx >= dy) std::nth_element(p + l, p + mid, p + r + 1, cmpByX);
        else std::nth_element(p + l, p + mid, p + r + 1, cmpByY);
        node[mid].lson = Build(l, mid - 1);
        node[mid].rson = Build(mid + 1, r);
        PushUp(mid);
        return mid;
    }

    void Query(int l, int r, int x) {
        if (l > r) return;
        int mid = (l + r) / 2;
        lxl t = square(p[mid].x - p[x].x) + square(p[mid].y - p[x].y);
        if (t > q.top()) q.pop(), q.push(t);
        lxl dl = dis(x, node[mid].lson);
        lxl dr = dis(x, node[mid].rson);
        if (dl > q.top() && dr > q.top()) {
            if (dl > dr) {
                Query(l, mid - 1, x);
                if (dr > q.top()) Query(mid + 1, r, x);
            } else {
                Query(mid + 1, r, x);
                if (dl > q.top()) Query(l, mid - 1, x);
            }
        } else {
            if (dl > q.top()) Query(l, mid - 1, x);
            if (dr > q.top()) Query(mid + 1, r, x);
        }
        return;
    }
} KDT;

signed main() {
    std::cin >> n >> k;
    k *= 2;
    for (int i = 1; i <= k; i++) q.push(0);
    for (int i = 1; i <= n; i++) std::cin >> p[i].x >> p[i].y;
    KDT.Build(1, n);
    for (int i = 1; i <= n; i++) KDT.Query(1, n, i);
    std::cout << q.top() << '\n';
    return 0;
}