#include <iostream>
#include <stack>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e4;
const int maxM = 5e4;

int n, m;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int daeh;
        int vis;
        int bel;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM + 10], egde[maxM + 10];

    int ecnt;
    int tnce;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void addEgde(int tail, int head) {
        tnce++;
        egde[tnce].head = head;
        egde[tnce].next = vertex[tail].daeh;
        vertex[tail].daeh = tnce;
        return;
    }

    std::stack<int> s;

    struct StronglyConnectedComponent {
        int size;
    } scc[maxN + 10];

    int scnt;

    void DFS(int u) {
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].vis) DFS(v);
        }
        s.push(u);
        return;
    }

    void Kosaraju(int u, int bel) {
        vertex[u].vis = true;
        vertex[u].bel = bel;
        scc[bel].size++;
        for (int e = vertex[u].daeh; e; e = egde[e].next) {
            int v = egde[e].head;
            if (!vertex[v].vis) Kosaraju(v, bel);
        }
        return;
    }
}

int ans;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a >> b, graph::addEdge(a, b), graph::addEgde(b, a);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].vis) graph::DFS(i);
    for (int i = 1; i <= n; i++) graph::vertex[i].vis = false;
    while (!graph::s.empty()) {
        int u = graph::s.top();
        graph::s.pop();
        graph::Kosaraju(u, ++graph::scnt);
    }
    for (int i = 1; i <= graph::scnt; i++) if (graph::scc[i].size > 1) ans++;
    std::cout << ans << '\n';
    return 0;
}