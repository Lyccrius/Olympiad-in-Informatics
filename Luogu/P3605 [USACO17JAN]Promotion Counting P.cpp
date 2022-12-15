#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int N;
int p[maxN];
int manager;
int range[maxN];

struct BinaryIndexedTree {
    struct Node {
        int val;
    } node[maxN];

    int lowbit(int x) {
        return x & -x;
    }

    void Add(int pos, int val) {
        while (pos <= N) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    int Ask(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret;
    }
} BIT;

namespace Graph {
    struct Vertex {
        int head;
        int cnt;
    } vertex[maxN];

    struct Edge {
        int head;
        int next;
    } edge[maxN];
    
    int ecnt;

    void AddEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    void DFS(int u) {
        vertex[u].cnt = BIT.Ask(p[u]) - BIT.Ask(N);
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            DFS(v);
        }
        vertex[u].cnt += BIT.Ask(N) - BIT.Ask(p[u]);
        BIT.Add(p[u], 1);
        return;
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &p[i]);
    for (int i = 1; i <= N; i++) range[i] = p[i];
    std::sort(range + 1, range + N + 1);
    for (int i = 1; i <= N; i++) p[i] = std::lower_bound(range + 1, range + N + 1, p[i]) - range;
    for (int i = 2; i <= N; i++) scanf("%d", &manager), Graph::AddEdge(manager, i);
    Graph::DFS(1);
    for (int i = 1; i <= N; i++) printf("%d\n", Graph::vertex[i].cnt);
    return 0;
}