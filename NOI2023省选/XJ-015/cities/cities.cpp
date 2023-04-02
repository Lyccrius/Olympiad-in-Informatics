#include <iostream>

const int maxN = 1e5;
const int maxM = 2e5;
const int mod = 998244353;

int n, m, k;
int u[maxM + 10], v[maxM + 10];

namespace graph {
    struct Vertex {
        int head;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int i;
    } edge[maxM * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head, int i) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].i = i;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }
}

namespace brute {
    int a[maxM + 10];
    int b[maxN + 10];
    int c[maxN + 10];
    int size[maxN + 10];
    int ans;

    int abs(int x) {
        if (x < 0) x = - x;
        return x;
    }

    void DFS(int u, int top) {
        size[u] = 1;
        b[u] = top;
        using namespace graph;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            if (a[edge[e].i]) continue;
            int v = edge[e].head;
            if (b[v]) continue;
            DFS(v, top);
            size[u] += size[v];
        }
        return;
    }

    bool check() {
        using namespace graph;
        for (int i = 1; i <= n; i++) b[i] = false;
        for (int i = 1; i <= n; i++) c[i] = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (b[i] == 0) {
                DFS(i, i);
                cnt++;
            }
        }
        if (cnt < 2) return false;
        int part = -1;
        for (int i = 1; i <= n; i++) {
            if (b[i] == i) {
                if (part == -1) {
                    part = size[i];
                } else {
                    if (abs(part - size[i]) > k) {
                        return false;
                    }
                }
            }
        }
        for (int i = 1; i <= m; i++) {
            if (a[i]) {
                if (b[u[i]] == b[v[i]]) {
                    return false;
                }
                if (c[b[u[i]]] == 0) {
                    c[b[u[i]]] = u[i];
                } else {
                    if (c[b[u[i]]] != u[i]) {
                        return false;
                    }
                }
                if (c[b[v[i]]] == 0) {
                    c[b[v[i]]] = v[i];
                } else {
                    if (c[b[v[i]]] != v[i]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void dfs(int now) {
        if (now > m) {
            if (check()) {
                /*
                printf("#######\n");
                for (int i = 1; i <= m; i++) {
                    if (a[i]) {
                        std::cout << u[i] << ' ' << v[i] << '\n';
                    }
                }
                std::cout << '\n' << '\n';
                */
                ans++;
            }
            return;
        }
        a[now] = true;
        dfs(now + 1);
        a[now] = false;
        dfs(now + 1);
        return;
    }

    void main() {
        dfs(1);
        std::cout << ans << '\n';
        return;
    }
}

/*
namespace brute2 {
    int a_[maxN + 10];
    int a[maxM + 10];
    int b[maxN + 10];
    int c[maxN + 10];
    int size[maxN + 10];
    int ans;

    int abs(int x) {
        if (x < 0) x = - x;
        return x;
    }

    void DFS(int u, int top) {
        size[u] = 1;
        b[u] = top;
        using namespace graph;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            if (a[edge[e].i]) continue;
            int v = edge[e].head;
            if (b[v]) continue;
            DFS(v, top);
            size[u] += size[v];
        }
        return;
    }

    bool check() {
        using namespace graph;
        for (int i = 1; i <= n; i++) b[i] = false;
        for (int i = 1; i <= n; i++) c[i] = 0;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (b[i] == 0) {
                DFS(i, i);
                cnt++;
            }
        }
        if (cnt < 2) return false;
        int part = -1;
        for (int i = 1; i <= n; i++) {
            if (b[i] == i) {
                if (part == -1) {
                    part = size[i];
                } else {
                    if (abs(part - size[i]) > k) {
                        return false;
                    }
                }
            }
        }
        for (int i = 1; i <= m; i++) {
            if (a[i]) {
                if (b[u[i]] == b[v[i]]) {
                    return false;
                }
                if (c[b[u[i]]] == 0) {
                    c[b[u[i]]] = u[i];
                } else {
                    if (c[b[u[i]]] != u[i]) {
                        return false;
                    }
                }
                if (c[b[v[i]]] == 0) {
                    c[b[v[i]]] = v[i];
                } else {
                    if (c[b[v[i]]] != v[i]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void ddfs(int now) {
        if (now > m) {
            if (check()) {
                ans++;
            }
        }
        if (a_[u[now]] && a_[v[now]]) {
            a[now] = true;
            ddfs(now + 1);
        }
        a[now] = false;
        ddfs(now + 1);
        return;
    }

    void dfs(int now) {
        if (now > n) {
            ddfs(1);
            return;
        }
        a_[now] = true;
        dfs(now + 1);
        a_[now] = false;
        dfs(now + 1);
        return;
    }

    void main() {
        dfs(1);
        std::cout << ans << '\n';
        return;
    }
}
*/

int main() {
    freopen("cities.in", "r", stdin);
    freopen("cities.out", "w", stdout);
    std::cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        std::cin >> u[i] >> v[i];
        graph::addEdge(u[i], v[i], i);
        graph::addEdge(v[i], u[i], i);
    }
    //if (m <= 20) 
    brute::main();
    //if (n <= 20) brute2::main();
    return 0;
}