#include <iostream>
#include <deque>
#include <map>

typedef std::deque<int> dic;
typedef std::map<int, std::map<int, int> > mii;

const int maxN = 3e5;
const int maxK = 3e5;

int n, k, d;
int p[maxK + 10];
int u, v;
dic ans;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int col;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    mii adj;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        adj[tail][head] = (ecnt + 1) / 2;
        return;
    }

    void BFS() {
        dic q;
        for (int i = 1; i <= k; i++) q.push_back(p[i]);
        for (int i = 1; i <= k; i++) vertex[p[i]].col = p[i];
        while (q.size()) {
            int u = q.front();
            q.pop_front();
            if (vertex[u].vis) continue;
            vertex[u].vis = true;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (vertex[v].vis) continue;
                if (vertex[v].col) ans.push_back(adj[u][v]);
                else vertex[v].col = vertex[u].col, q.push_back(v);
            }
        }
        return;
    }
}

int main() {
    std::cin >> n >> k >> d;
    for (int i = 1; i <= k; i++) std::cin >> p[i];
    for (int i = 1; i < n; i++) std::cin >> u >> v, graph::addEdge(u, v), graph::addEdge(v, u);
    graph::BFS();
    std::cout << ans.size() << '\n';
    for (auto i : ans) std::cout << i << ' ';
    return 0;
}