#include <iostream>
#include <vector>

typedef char chr;
typedef std::vector<int> vic;

const int maxN = 2000;
const int mod = 998244353;

int n;
chr s[maxN + 10][maxN + 10];
int f[2 * maxN + 10];
int ans = 1;
int cnt;

namespace graph {
    struct Vertex {
        int head;
        int deg;
        int vis;
        int ins;
    } vertex[2 * maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[head].deg++;
        return;
    }

    bool DFS(int u) {
        vertex[u].vis = true;
        vertex[u].ins = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (!vertex[v].vis) {
                if (DFS(v)) return true;
            } else if (vertex[v].ins) return true;
        }
        vertex[u].ins = false;
        return false;
    }

    void topo() {
        vic t;
        vic q;
        for (int i = 1; i <= 2 * n; i++) if (vertex[i].deg == 0) t.push_back(i);
        while (t.size()) {
            q = t;
            t.clear();
            ans = 1ll * ans * f[q.size()] % mod;
            cnt += q.size();
            for (int i = 0; i < q.size(); i++) {
                int u = q[i];
                for (int e = vertex[u].head; e; e = edge[e].next) {
                    int v = edge[e].head;
                    vertex[v].deg--;
                    if (vertex[v].deg == 0) t.push_back(v);
                }
            }
        }
        return;
    }
}

int main() {
    f[0] = 1;
    for (int i = 1; i <= 2 * maxN; i++) f[i] = 1ll * f[i - 1] * i % mod;
    std::cin >> n;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) std::cin >> s[i][j];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (s[i][j] == '0') graph::addEdge(i, j + n);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (s[i][j] == '1') graph::addEdge(j + n, i);
    for (int i = 1; i <= n; i++) if (!graph::vertex[i].vis) if (graph::DFS(i)) {std::cout << 0 << '\n'; return 0;};
    graph::topo();
    std::cout << ans << '\n';
    return 0;
}