#include <iostream>

const int maxN = 2e5;
const int mod = 998244353;

int n;
int u, v;
int p1, p2;
int d;

namespace graph {
    struct Vertex {
        int head;
        int dep;
        int fa;
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

    void AddEdge(int tail, int head) {
        addEdge(tail, head);
        addEdge(head, tail);
        return;
    }

    void DFS(int u, int from) {
        vertex[u].fa = from;
        vertex[u].dep = vertex[from].dep + 1;
        if (vertex[u].dep > vertex[p2].dep) p2 = u;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
        }
        return;
    }

    int DFS2(int u, int from) {
        int ret = 0;
        vertex[u].dep = vertex[from].dep + 1;
        //printf("dep %d = %d\n", u, vertex[u].dep);
        if (vertex[u].dep == (d - 1) / 2) ret++;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            ret += DFS2(v, u);
        }
        return ret;
    }
}

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

void solve1() {
    int u = p2;
    while (graph::vertex[u].dep != (d + 1) / 2) u = graph::vertex[u].fa;
    //graph::DFS(u, 0);
    int ans = 1;
    int cnt = 0;
    graph::vertex[u].dep = 0;
    for (int e = graph::vertex[u].head; e; e = graph::edge[e].next) {
        int v = graph::edge[e].head;
        int t = graph::DFS2(v, u);
        //printf("%d: %d\n", v, t);
        ans = 1ll * ans * (t + 1) % mod;
        cnt += t;
    }
    std::cout << (ans - cnt - 1) % mod << '\n';
    return;
}

void solve2() {
    int u = p2;
    int a = 0, b =0 ;
    while (graph::vertex[graph::vertex[u].fa].dep * 2 != d) u = graph::vertex[u].fa;
    for (int i = 1; i <= n; i++) graph::vertex[i].dep = 0;
    graph::DFS(graph::vertex[u].fa, u);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].dep * 2 == d) a++;
    for (int i = 1; i <= n; i++) graph::vertex[i].dep = 0;
    graph::DFS(u, graph::vertex[u].fa);
    for (int i = 1; i <= n; i++) if (graph::vertex[i].dep * 2 == d) b++;
    std::cout << 1ll * a * b % mod << '\n';
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n - 1; i++) std::cin >> u >> v, graph::AddEdge(u, v);
    graph::DFS(1, 0);
    p1 = p2;
    graph::DFS(p2, 0);
    d = graph::vertex[p2].dep;
    if (d & 1) solve1();
    else solve2();
    return 0;
}