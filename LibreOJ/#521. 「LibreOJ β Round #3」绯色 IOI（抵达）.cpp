#include <iostream>
#include <vector>
#include <queue>

typedef std::vector<int> vic;

const int maxN = 5e5;

int n, m;
int u, v;
vic a;

struct Graph {
    struct Vertex {
        int match;
        int head;
        int size;
        int cnt;
        int deg;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].deg++;
        return;
    }

    void DFS(int u, int from) {
        vertex[u].size = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            vertex[u].size += vertex[v].size;
        }
        if (vertex[u].size & 1) {
            vertex[u].match = from;
            vertex[from].cnt++;
        } else {
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                if (vertex[v].size & 1) {
                    vertex[v].cnt++;
                    vertex[u].match = v;
                    break;
                }
            }
        }
        return;
    }

    void toposort() {
        std::priority_queue<int, std::vector<int>,  std::greater<int> > q;
        for (int u = 1; u <= n; u++) if (!vertex[u].deg) q.push(u);
        while (!q.empty()) {
            int u = q.top();
            q.pop();
            a.push_back(u);
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                vertex[v].deg--;
                if (!vertex[v].deg) q.push(v);
            }
        }
        return;
    }
} tree, dag;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, tree.addEdge(u, v), tree.addEdge(v, u);
    tree.DFS(1, 0);
    for (int i = 1; i <= n; i++) if (tree.vertex[i].cnt != 1) {std::cout << -1 << '\n'; return 0;}
    for (int u = 1; u <= n; u++) {
        for (int e = tree.vertex[u].head; e; e = tree.edge[e].next) {
            int v = tree.edge[e].head;
            if (v == tree.vertex[u].match) continue;
            dag.addEdge(tree.vertex[u].match, v);
        }
    }
    dag.toposort();
    for (auto i : a) std::cout << i << ' ';
    return 0;
}