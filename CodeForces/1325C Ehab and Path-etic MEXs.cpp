#include <iostream>
#include <vector>
#include <map>

const int maxN = 1e5;

int n;
int u, v;
std::map<int, std::map<int, int> > adj;
std::vector<int> out[maxN + 10];
int cur;
int ans[maxN + 10];
int tot = 3;

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> u >> v;
        adj[u][v] = i;
        adj[v][u] = i;
        out[u].push_back(v);
        out[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (out[i].size() >= 3) {cur = i; break;}
    if (!cur) {
        for (int i = 0; i <= n - 2; i++) std::cout << i << '\n';
        return 0;
    }
    for (int i = 0; i < 3; i++) ans[adj[cur][out[cur][i]]] = - i - 1;
    for (int i = 1; i < n && tot <= n - 2; i++) {
        if (ans[i]) continue;
        ans[i] = tot;
        tot++;
    }
    for (int i = 1; i < n; i++) {
        if (ans[i] < 0) ans[i] = - ans[i] - 1;
        std::cout << ans[i] << '\n';
    }
    return 0;
}