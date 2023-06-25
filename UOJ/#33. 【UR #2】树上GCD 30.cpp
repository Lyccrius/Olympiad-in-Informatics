#include <iostream>

typedef long long lxl;

const int maxN = 200000;
const int logN = 50;

int n;
int p[maxN + 10];
int gcd[logN + 10][logN + 10];
lxl ans[maxN + 10];

int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int h;
        lxl cnt[logN + 10];
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
        return;
    }

    void DFS(int u, int from) {
        vertex[u].cnt[0] = 1;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            for (int i = 0; i <= vertex[u].h; i++) {
                for (int j = 0; j <= vertex[v].h; j++) {
                    ans[gcd[i][j + 1]] += vertex[u].cnt[i] * vertex[v].cnt[j];
                }
            }
            for (int j = 0; j <= vertex[v].h; j++) {
                vertex[u].cnt[j + 1] += vertex[v].cnt[j];
            }
            vertex[u].h = std::max(vertex[u].h, vertex[v].h + 1);
        }
        return;
    }
}

int main() {
    for (int i = 0; i <= logN; i++) for (int j = 0; j <= logN; j++) gcd[i][j] = GCD(i, j);
    std::cin >> n;
    for (int i = 2; i <= n; i++) std::cin >> p[i];
    for (int i = 2; i <= n; i++) graph::addEdge(p[i], i), graph::addEdge(i, p[i]);
    graph::DFS(1, 0);
    for (int i = 1; i <= n - 1; i++) std::cout << ans[i] << '\n';
    return 0;
}