#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 5e4;
const int maxM = 5e4;
const lxl inf = 1e18;

int n, m;
int op, a, b, c;

namespace graph {
    struct Vertex {
        int head;
        int inq;
        int cnt;
        lxl dis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int weight;
    } edge[maxM * 2 + maxN + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool SPFA(int s) {
        std::queue<int> q;
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        vertex[s].dis = 0;
        vertex[s].inq = true;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vertex[u].inq = false;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w) {
                    vertex[v].dis = vertex[u].dis + w;
                    if (!vertex[v].inq) {
                        vertex[v].inq = true;
                        q.push(v);
                        vertex[v].cnt++;
                        if (vertex[v].cnt >= n) return true;
                    }
                }
            }
        }
        return false;
    }
}
        
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> a >> b >> c;
            graph::addEdge(b, a, -c);
        } else if (op == 2) {
            std::cin >> a >> b >> c;
            graph::addEdge(a, b, c);
        } else {
            std::cin >> a >> b;
            graph::addEdge(a, b, 0);
            graph::addEdge(b, a, 0);
        }
    }
    for (int i = 1; i <= n; i++) graph::addEdge(0, i, 0);
    if (graph::SPFA(0)) std::cout << "No";
    else std::cout << "Yes";
    return 0;
}