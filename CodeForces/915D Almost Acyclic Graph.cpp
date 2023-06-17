#include <iostream>
#include <deque>

typedef std::deque<int> diq;

const int maxN = 500;
const int maxM = 1e5;

int n, m;
int u[maxM + 10], v[maxM + 10];

namespace graph {
    struct Vertex {
        int head;
        int deg;
        int bak;
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
        vertex[head].deg++;
        vertex[head].bak++;
        return;
    }

    void clear() {
        for (int i = 1; i <= n; i++) vertex[i].deg = vertex[i].bak;
        return;
    }

    int toposort() {
        diq q;
        int ret = 0;
        for (int i = 1; i <= n; i++) if (vertex[i].deg == 0) q.push_back(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            ret++;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                vertex[v].deg--;
                if (vertex[v].deg == 0) q.push_back(v);
            }
        }
        return ret;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> u[i] >> v[i];
    for (int j = 1; j <= m; j++) graph::addEdge(u[j], v[j]);
    for (int i = 1; i <= n; i++) {
        graph::clear();
        graph::vertex[i].deg--;
        if (graph::toposort() == n) {
            std::cout << "YES" << '\n';
            return 0;
        }
    }
    std::cout << "NO" << '\n';
    return 0;
}