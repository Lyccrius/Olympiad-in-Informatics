#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 2e5;
const int mod = 1e9 + 7;


int n, x, y;
int u, v;

int fac[maxN + 10];
int cnt;
int ans;

void init() {
    fac[0] = 1;
    for (int i = 1; i <= maxN; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    return;
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

int b[maxN + 10][2];
int a[maxN + 10];

namespace graph {
    struct Vertex {
        int head;
        int deg;
        int vis;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int col;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int col) {
        ecnt++;
        edge[ecnt].col = col;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        vertex[tail].deg++;
        return;
    }

    int DFS(int u, int &col) {
        if (vertex[u].vis) return 0;
        vertex[u].vis = true;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int c = edge[e].col;
            if (vertex[v].vis) continue;
            col = c;
            return DFS(v, col) + 1;
        }
        return 1;
    }

    void link() {
        int c, x;
        for (int u = 1; u <= n; u++) {
            if (vertex[u].vis) continue;
            if (vertex[u].deg != 1) continue;
            x = DFS(u, c);
            b[x][c]++;
        }
        return;
    }

    void ring() {
        int c, x;
        for (int u = 1; u <= n; u++) {
            if (vertex[u].vis) continue;
            int t = DFS(u, x);
            a[t]++;
        }
        return;
    }

    void mian() {
        for (int i = 1; i <= n; i++) {
            ans = 1ll * ans * fac[a[i]] % mod * pow(i, a[i]) % mod;
            if (i & 1) {
                ans = 1ll * ans * fac[b[i][0] + b[i][1]] % mod;
            } else {
                ans = 1ll * ans * fac[b[i][0]] % mod * fac[b[i][1]] % mod * pow(2, b[i][0] + b[i][1]) % mod;
            }
        }
        return;
    }
}

int main() {
    init();
    std::cin >> n >> x >> y;
    for (int i = 1; i <= x; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v, 1);
        graph::addEdge(v, u, 1);
    }
    for (int i = 1; i <= y; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v, 0);
        graph::addEdge(v, u, 0);
    }
    for (int u = 1; u <= n; u++) {
        if (graph::vertex[u].deg == 0) {
            graph::vertex[u].vis = true;
            cnt++;
        }
    }
    ans = fac[cnt];
    graph::ring();
    graph::link();
    graph::mian();
    std::cout << ans << '\n';
    return 0;
}