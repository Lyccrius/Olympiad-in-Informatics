#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;
const int maxM = 5e5;
const int inf = 1e9;

int n, m;
int p[maxN + 10];
int x, y, z;

namespace graph {
    struct Vertex {
        int head;
        int dfn;
        int low;
        int ins;
        int bel;
        int deg;
    };

    struct Edge {
        int head;
        int next;
    };

    Vertex vertex[maxN * 2 + 10];
    Edge edge[maxM * 2 * 2 + 10];
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

    struct SCC {
        int minP;
        int maxP;
        int minF;
        int maxF;
        int f;
    };

    SCC scc[maxN + 10];
    int scnt;

    void addSCC(int u) {
        scnt++;
        int v;
        scc[scnt].minP = inf;
        scc[scnt].maxP = - inf;
        do {
            v = s.top();
            s.pop();
            vertex[v].ins = false;
            vertex[v].bel = scnt;
            scc[scnt].minP = std::min(scc[scnt].minP, p[v]);
            scc[scnt].maxP = std::max(scc[scnt].maxP, p[v]);
        } while (v != u);
        scc[scnt].maxF = scc[scnt].maxP - scc[scnt].minP;
        return;
    }

    void Tarjan(int u) {
        dfn++;
        vertex[u].dfn = dfn;
        vertex[u].low = dfn;
        vertex[u].ins = true;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].dfn == 0) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        if (vertex[u].dfn == vertex[u].low) addSCC(u);
        return;
    }

    std::vector<int> topo;

    void TopoSort() {
        std::queue<int> q;
        q.push(vertex[1].bel + n);
        while (!q.empty()) {
            int s = q.front();
            q.pop();
            topo.push_back(s - n);
            for (int e = vertex[s].head; e; e = edge[e].next) {
                int t = edge[e].head;
                vertex[t].deg--;
                if (vertex[t].deg == 0) {
                    q.push(t);
                }
            }
        }
        return;
    }

    void mian() {
        for (int u = 1; u <= n; u++) {
            if (!vertex[u].dfn) {
                Tarjan(u);
            }
        }
        for (int u = 1; u <= n; u++) {
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[u].bel != vertex[v].bel) {
                    addEdge(vertex[u].bel + n, vertex[v].bel + n);
                    vertex[vertex[v].bel + n].deg++;
                }
            }
        }
        TopoSort();
        scc[topo.front()].minF = scc[topo.front()].minP;
        for (auto s : topo) {
            for (int e = vertex[s + n].head; e; e = edge[e].next) {
                int t = edge[e].head - n;
                scc[t].minF = std::min(scc[t].minP, scc[s].minF);
                scc[t].f = std::max(scc[t].f, scc[s].f);
                scc[t].f = std::max(scc[t].f, scc[t].maxF);
                scc[t].f = std::max(scc[t].f, scc[t].maxP - scc[t].minF);
            }
        }
        std::cout << scc[vertex[n].bel].f;
        return;
    }
}

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y >> z;
        if (z == 1) {
            graph::addEdge(x, y);
        }else{
            graph::addEdge(x, y);
            graph::addEdge(y, x);
        }
    }
    graph::mian();
    return 0;
}