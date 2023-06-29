#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 200;
const int maxM = 10000;
const int maxA = 255;
const int maxB = 255;
const int inf = maxM * maxA * maxB;

int n, m;
int u, v, a, b;

struct Point {
    int x, y;

    Point operator-(Point other) const {
        return (Point) {x - other.x, y - other.y};
    }

    int cross(Point other) {
        return x * other.y - y * other.x;
    }

    int vert() {
        return x * y;
    }
} ans = {inf, inf};

namespace graph {
    struct Edge {
        int u, v;
        int a, b;
        int w;

        bool operator<(Edge other) const {
            return w < other.w;
        }
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int u, int v, int a, int b) {
        edge[++ecnt] = (Edge) {u + 1, v + 1, a, b};
        return;
    }

    struct DisjointSetUnion {
        struct Node {
            int fa;
        } node[maxN + 10];

        void Init() {
            for (int i = 1; i <= n; i++) node[i].fa = i;
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return node[u].fa = Find(node[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            if (u == v) return;
            node[u].fa = v;
            return;
        }
    } DSU;

    Point Kruscal() {
        Point ret = (Point) {0, 0};
        DSU.Init();
        std::sort(edge + 1, edge + m + 1);
        for (int i = 1; i <= m; i++) {
            int u = edge[i].u;
            int v = edge[i].v;
            int a = edge[i].a;
            int b = edge[i].b;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            DSU.Union(u, v);
            ret.x += a;
            ret.y += b;
        }
        if (ans.vert() > ret.vert()) ans = ret;
        if (ans.vert() == ret.vert() && ans.x > ret.x) ans = ret;
        return ret;
    }
}

void solve(Point A, Point B) {
    for (int i = 1; i <= m; i++) graph::edge[i].w = (A.y - B.y) * graph::edge[i].a + (B.x - A.x) * graph::edge[i].b;
    Point C = graph::Kruscal();
    if ((B - A).cross(C - A) >= 0) return;
    solve(A, C);
    solve(C, B);
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u >> v >> a >> b, graph::addEdge(u, v, a, b);
    for (int i = 1; i <= m; i++) graph::edge[i].w = graph::edge[i].a;
    Point A = graph::Kruscal();
    for (int i = 1; i <= m; i++) graph::edge[i].w = graph::edge[i].b;
    Point B = graph::Kruscal();
    solve(A, B);
    std::cout << ans.x << ' ' << ans.y;
    std::cout << '\n';
    return 0;
}