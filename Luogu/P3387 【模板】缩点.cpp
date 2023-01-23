#include <algorithm>
#include <iostream>
#include <stack>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e4;
const int maxM = 1e5;
const int maxA = 1e3;

int n, m;
int a[maxN + 10];
int u, v;

int ans;

namespace graph {
    struct Vertex {
        int head;
        int low;
        int dfn;
        int ins;
        int bel;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    int dfn;
    std::stack<int> s;

    struct StronglyConnectedComponent {
        int res;
    } scc[maxN + 10];
    
    int scnt;

    void addSCC(int u) {
        scnt++;
        int v;
        int res = 0;
        do {
            v = s.top();
            s.pop();
            vertex[v].ins = false;
            vertex[v].bel = scnt;
            res += a[v];
            for (int e = vertex[v].head; e; e = edge[e].next) {
                int w = edge[e].head;
                int s = vertex[w].bel;
                scc[scnt].res = std::max(scc[scnt].res, scc[s].res);
            }
        } while (v != u);
        scc[scnt].res += res;
        ans = std::max(ans, scc[scnt].res);
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].low = dfn;
        vertex[u].dfn = dfn;
        vertex[u].ins = true;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        if (vertex[u].low == vertex[u].dfn) addSCC(u);
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> u >> v, graph::addEdge(u, v);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    std::cout << ans << '\n';
    return 0;
}