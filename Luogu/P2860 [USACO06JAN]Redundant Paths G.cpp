#include <iostream>
#include <stack>

const int maxF = 5000;
const int maxR = 10000;

int F, R;
int b, e;

namespace graph {
    struct Vertex {
        int head;
        int low;
        int dfn;
        int bel;
    } vertex[maxF + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxR * 2 + 10];

    int ecnt;

    int adjacency[maxF + 10][maxF + 10];

    void addEdge(int tail, int head) {
        if (adjacency[tail][head]) return;
        adjacency[tail][head] = true;
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    struct Block {
        int degree;
    } block[maxF + 10];

    int bcnt;

    int cnt;
    std::stack<int> s;

    void DFS(int u, int from) {
        cnt++;
        vertex[u].low = cnt;
        vertex[u].dfn = cnt;
        s.push(u);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            if (!vertex[v].dfn) {
                DFS(v, u);
                vertex[u].low = std::min(vertex[u].low, vertex[v].low);
            } else vertex[u].low = std::min(vertex[u].low, vertex[v].dfn);
        }
        if (vertex[u].low == vertex[u].dfn) {
            bcnt++;
            int v;
            do {
                v = s.top();
                s.pop();
                vertex[v].bel = bcnt;
            } while (v != u);
        }
        return;
    }

    void mian() {
        for (int e1 = 1; e1 <= ecnt; e1 += 2) {
            int e2 = e1 + 1;
            int u = edge[e1].head;
            int v = edge[e2].head;
            if (vertex[u].bel != vertex[v].bel) {
                block[vertex[u].bel].degree++;
                block[vertex[v].bel].degree++;
            }
        }
        int ans = 0;
        for (int b = 1; b <= bcnt; b++) if (block[b].degree == 1) ans++;
        ans = (ans + 1) / 2;
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    std::cin >> F >> R;
    for (int i = 1; i <= R; i++) std::cin >> b >> e, graph::addEdge(b, e), graph::addEdge(e, b);
    graph::DFS(1, 0);
    graph::mian();
    return 0;
}