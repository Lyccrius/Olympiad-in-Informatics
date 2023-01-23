#include <iostream>
#include <vector>
#include <stack>

typedef std::vector<int> vic;

const int maxN = 2e4;
const int maxM = 1e5;

int n, m;
int x, y;

namespace graph {
    struct Vertex {
        int degree;
        int head;
        int low;
        int dfn;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxM * 2 + 10];

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

    int vbcccnt;

    void addVBCC(int u) {
        vbcccnt++;
        int v;
        do {
            v = s.top();
            s.pop();
            vertex[v].degree++;
        } while (v != u);
        return;
    }

    void DFS(int u, int from) {
        dfn++;
        vertex[u].low = dfn;
        vertex[u].dfn = dfn;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                DFS(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
                if (vertex[v].low >= vertex[u].dfn) {
                    s.push(u);
                    addVBCC(v);
                }
            } else vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        return;
    }

    void mian() {
        for (int i = 1; i <= n; i++) {
            if (!vertex[i].dfn) {
                DFS(i, 0);
                while (!s.empty()) s.pop();
            }
        }
        vic ans;
        for (int i = 1; i <= n; i++) if (vertex[i].degree > 1) ans.push_back(i);
        std::cout << ans.size() << '\n';
        for (auto i : ans) std::cout << i << ' ';
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> x >> y, graph::addEdge(x, y), graph::addEdge(y, x);
    graph::mian();
    return 0;
}