#include <iostream>
#include <algorithm>

typedef std::pair<int, int> pii;

const int maxN = 3e5;
const int mod = 998244353;

int n;
int a[maxN + 10];
int u[maxN + 10], v[maxN + 10];

namespace S1 {
    bool is() {
        return n <= 18;
    }

    int b[maxN + 10];
    int ans;

    struct DisjointSetUnion {
        struct Node {
            int val;
            int fa;
        } node[maxN + 10];

        void Init() {
            for (int i = 1; i <= n; i++) node[i].val = a[i];
            for (int i = 1; i <= n; i++) node[i].fa = i;
            return;
        }

        int Find(int u) {
            if (node[u].fa == u) return u;
            return Find(node[u].fa);
        }

        void Union(int u, int v) {
            u = Find(u);
            v = Find(v);
            if (u == v) return;
            node[u].fa = v;
            node[v].val = std::min(node[u].val, node[v].val);
            return;
        }
    } DSU;

    void update() {
        DSU.Init();
        for (int i = 1; i < n; i++) {
            if (b[i]) {
                DSU.Union(u[i], v[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (DSU.Find(i) == i) {
                ans = (ans + DSU.node[i].val) % mod;
                //printf("%d ", DSU.node[i].val);
            }
        }
        //printf("\n");
        return;
    }

    void DFS(int now) {
        if (now == n) {
            update();
            return;
        }
        b[now] = 1;
        DFS(now + 1);
        b[now] = 0;
        DFS(now + 1);
        return;
    }

    void mian() {
        DFS(1);
        std::cout << ans << '\n';
        return;
    }
}

namespace S2 {
    bool is() {
        return n <= 5000;
    }

    int ans;

    namespace graph {
        struct Vertex {
            int head;
            int size;
            int pro;
            int any;
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

        void DFS1(int u, int from) {
            vertex[u].size = 1;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                DFS1(v, u);
                vertex[u].size += vertex[v].size;
            }
            return;
        }

        void DFS2(int u, int from, int val) {
            vertex[u].pro = 1;
            vertex[u].any = 0;
            for (int e = vertex[u].head; e; e = edge[e].next) {
                int v = edge[e].head;
                if (v == from) continue;
                if (a[v] < val) {
                    vertex[u].any += vertex[v].size - 1;
                } else {
                    DFS2(v, u, val);
                    vertex[u].pro = 1ll * vertex[u].pro * (vertex[v].pro + 1) % mod;
                    vertex[u].any = (vertex[u].any + vertex[v].any) % mod;
                }
            }
            return;
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

    void mian() {
        for (int i = 1; i < n; i++) {
            graph::addEdge(u[i], v[i]);
            graph::addEdge(v[i], u[i]);
        }
        for (int i = 1; i <= n; i++) {
            graph::DFS1(i, 0);
            graph::DFS2(i, 0, a[i]);
            //graph::DFS3(i, 0, a[i]);
            ans = (ans + 1ll * a[i] * graph::vertex[i].pro % mod * pow(2, graph::vertex[i].any) % mod) % mod;
            /*
            printf("pro[%d] = %d\n", i, graph::vertex[i].pro);
            printf("any[%d] = %d\n", i, graph::vertex[i].any);
            printf("%d\n", graph::vertex[i].pro % mod * pow(2, graph::vertex[i].any) % mod);
            printf("\n");
            */
        }
        std::cout << ans << '\n';
        return;
    }
}

int main() {
    freopen("toptree.in", "r", stdin);
    freopen("toptree.out", "w", stdout);
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i < n; i++) std::cin >> u[i] >> v[i];
    if (S1::is()) S1::mian();
    else if (S2::is()) S2::mian();
    return 0;
}