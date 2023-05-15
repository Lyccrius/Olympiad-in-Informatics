#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> vic;

const int maxN = 1e5;
const int sqrN = 1289;

int n;
int u, v;

namespace graph {
    struct Vertex {
        int head;
        int left;
        vic son;
        int dfn;
        int res;
        int fir;
        int sec;

        Vertex() {
            head = -1;
            return;
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

    int dfn;
    int dnf[maxN + 10];

    void DFS(int u, int from) {
        dfn++;
        vertex[u].dfn = dfn;
        dnf[vertex[u].dfn] = u;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            vertex[u].son.push_back(v);
            DFS(v, u);
        }
        return;
    }

    void solve(int u, int k) {
        vertex[u].res = 0;
        vertex[u].fir = 0;
        vertex[u].sec = 0;
        for (auto v : vertex[u].son) {
            vertex[u].res += vertex[v].res;
            vertex[u].sec = std::max(vertex[u].sec, vertex[v].left);
            if (vertex[u].sec > vertex[u].fir) std::swap(vertex[u].fir, vertex[u].sec);
        }
        if (vertex[u].fir + vertex[u].sec + 1 >= k) {
            vertex[u].left = 0;
            vertex[u].res++;
        } else {
            vertex[u].left = vertex[u].fir + 1;
        }
        return;
    }
}

int vis[maxN + 10];
int ans[maxN + 10];

int solve(int k) {
    if (vis[k]) return ans[k];
    for (int i = n; i >= 1; i--) graph::solve(graph::dnf[i], k);
    ans[k] = graph::vertex[1].res;
    vis[k] = true;
    return ans[k];
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        graph::addEdge(u, v);
        graph::addEdge(v, u);
    }
    graph::DFS(1, 0);
    for (int k = 1; k <= n; k++) {
        solve(k);
        if (k <= sqrN) {
            std::cout << ans[k] << '\n';
            continue;
        }
        int l = k;
        int r = std::min(k + sqrN - 1, n);
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (solve(k) == solve(mid)) l = mid;
            else r = mid - 1;
        }
        for (int i = k; i <= r; i++) std::cout << ans[k] << '\n';
        k = r;
    }
    return 0;
}