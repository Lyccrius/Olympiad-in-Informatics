#include <iostream>
#include <vector>

typedef std::vector<int> vic;

const int maxN = 5e5;
const int maxM = 5e5;

int n, m, s;
int x, y;
int a, b;

namespace graph {
    struct Vertex {
        int head;
        int rank;

        Vertex() {
            head = -1;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[2 * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    vic euler;

    void DFS(int u, int from) {
        vertex[u].rank = euler.size();
        euler.push_back(u);
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            euler.push_back(u);
        }
        return;
    }
}

struct SegmentTree {
    struct Node {
        int val;
    } node[4 * 2 * maxN + 10];
    
    void PushUp(int u) {
        node[u].val = std::min(node[2 * u].val, node[2 * u + 1].val);
        return;
    }

    void Build(int u, int l, int r) {
        if (l == r) {
            node[u].val = graph::vertex[graph::euler[l]].rank;
            return;
        }
        int mid = (l + r) / 2;
        Build(2 * u, l, mid);
        Build(2 * u + 1, mid + 1, r);
        PushUp(u);
        return;
    }

    int Query(int u, int l, int r, int s, int t) {
        if (s <= l && r <= t) {
            return node[u].val;
        }
        int mid = (l + r) / 2;
        if (t <= mid) return Query(2 * u, l, mid, s, t);
        if (s >= mid + 1) return Query(2 * u + 1, mid + 1, r, s, t);
        return std::min(Query(2 * u, l, mid, s, t), Query(2 * u + 1, mid + 1, r, s, t));
    }
} SGT;

int main() {
    std::cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        std::cin >> x >> y;
        graph::addEdge(x, y);
        graph::addEdge(y, x);
    }
    graph::DFS(s, 0);
    SGT.Build(1, 0, 2 * n - 1);
    for (int i = 1; i <= m; i++) {
        std::cin >> a >> b;
        if (graph::vertex[a].rank > graph::vertex[b].rank) std::swap(a, b);
        std::cout << graph::euler[SGT.Query(1, 0, 2 * n - 1, graph::vertex[a].rank, graph::vertex[b].rank)] << '\n';
    }
    return 0;
}