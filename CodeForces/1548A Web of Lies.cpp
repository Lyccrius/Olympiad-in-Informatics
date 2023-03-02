#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 2e5;
const int maxQ = 2e5;

int n, m;
int u, v;
int q;
int op;
int deg[maxN + 10];
int ans;

void addEdge(int u, int v) {
    if (u > v) std::swap(u, v);
    if (deg[u] == 0) ans--;
    deg[u]++;
    return;
}

void delEdge(int u, int v) {
    if (u > v) std::swap(u, v);
    deg[u]--;
    if (deg[u] == 0) ans++;
    return;
}

int main() {
    promote();
    std::cin >> n >> m; ans = n;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        addEdge(u, v);
    }
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) {
            std::cin >> u >> v;
            addEdge(u, v);
        } else if (op == 2) {
            std::cin >> u >> v;
            delEdge(u, v);
        } else if (op == 3) {
            std::cout << ans << '\n';
        }
    }
    return 0;
}