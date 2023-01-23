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

    int cnt;
    std::stack<int> s;

    struct StronglyConnectedComponent {
        int size;
    } scc[maxN + 10];

    int scnt;

    void addSSC(int u) {
        scnt++;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[v].ins = false;
            vertex[v].bel = scnt;
            scc[scnt].size++;
        } while (v != u);
        return;
    }

    void Tarjan(int u) {
        cnt++;
        vertex[u].low = cnt;
        vertex[u].dfn = cnt;
        vertex[u].ins = true;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].dfn) {
                Tarjan(v);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else if (vertex[v].ins) {
                vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
            }
        }
        if (vertex[u].low == vertex[u].dfn) addSSC(u);
        return;
    }
}

int ans;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a >> b, graph::addEdge(a, b);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].dfn) graph::Tarjan(i);
    for (int i = 1; i <= graph::scnt; i++) if (graph::scc[i].size > 1) ans++;
    std::cout << ans << '\n';
    return 0;
}