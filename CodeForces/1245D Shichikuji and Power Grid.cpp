#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::pair<int, int> pii;
typedef std::vector<int> vic;
typedef std::vector<pii> vpc;

const int maxN = 2000;

int n;
vic vec;
vpc vek;

namespace graph {
    struct Vertex {
        lxl x, y;
        lxl c, k;
        int fa;
    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        lxl weight;

        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    } edge[maxN + maxN * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, lxl weight) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        return;
    }

    struct DisjiontSetUnion {
        int Find(int u) {
            if (u == vertex[u].fa) return u;
            return vertex[u].fa = Find(vertex[u].fa);
        }

        void Union(int u, int v) {
            u = vertex[u].fa;
            v = vertex[v].fa;
            vertex[u].fa = v;
            return;
        }
    } DSU;

    lxl dis(int u, int v) {
        return std::abs(vertex[u].x - vertex[v].x) + std::abs(vertex[u].y - vertex[v].y);
    }

    lxl Kruscal() {
        lxl ret = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i++) vertex[i].fa = i;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int i = 1; i <= ecnt; i++) {
            int u = edge[i].tail;
            int v = edge[i].head;
            lxl w = edge[i].weight;
            int fu = DSU.Find(u);
            int fv = DSU.Find(v);
            if (fu == fv) continue;
            if (u && v) vek.push_back(std::make_pair(u, v));
            else if (u) vec.push_back(u); else vec.push_back(v);
            DSU.Union(u, v);
            ret += w;
            cnt++;
            if (cnt == n) break;
        }
        return ret;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> graph::vertex[i].x >> graph::vertex[i].y;
    for (int i = 1; i <= n; i++) std::cin >> graph::vertex[i].c, graph::addEdge(i, 0, graph::vertex[i].c);
    for (int i = 1; i <= n; i++) std::cin >> graph::vertex[i].k;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) graph::addEdge(i, j, (graph::vertex[i].k + graph::vertex[j].k) * graph::dis(i, j));
    std::cout << graph::Kruscal() << '\n';
    std::cout << vec.size() << '\n';
    if (vec.size()) {
        for (auto i : vec) std::cout << i << ' ';
        std::cout << '\n';
    }
    std::cout << vek.size() << '\n';
    if (vek.size()) {
        for (auto i : vek) std::cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}