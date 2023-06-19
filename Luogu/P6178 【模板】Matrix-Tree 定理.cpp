#include <iostream>

const int mod = 1e9 + 7;
const int maxN = 300;
const int maxM = 1e5;

int n, m, t;
int u, v, w;

struct Matrix {
    int n;
    int a[maxN + 10][maxN + 10];

    int vert() {
        int ret = 1;
        int sym = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                while (a[i][i]) {
                    int x = a[j][i] / a[i][i];
                    for (int k = i; k <= n; k++) {
                        a[j][k] = (a[j][k] - 1ll * x * a[i][k] % mod + mod) % mod;
                    }
                    std::swap(a[i], a[j]);
                    sym = - sym;
                }
                std::swap(a[i], a[j]);
                sym = - sym;
            }
        }
        for (int i = 1; i <= n; i++) ret = 1ll * ret * a[i][i] % mod;
        return (sym * ret % mod + mod) % mod;
    }
} L;

int main() {
    std::cin >> n >> m >> t;
    L.n = n;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        u--;
        v--;
        if (t) {
            L.a[u][v] = (L.a[u][v] - w) % mod;
            L.a[v][v] = (L.a[v][v] + w) % mod;
        } else {
            L.a[v][u] = (L.a[v][u] - w) % mod;
            L.a[v][v] = (L.a[v][v] + w) % mod;
            L.a[u][v] = (L.a[u][v] - w) % mod;
            L.a[u][u] = (L.a[u][u] + w) % mod;
        }
    }
    L.n--;
    std::cout << L.vert() << '\n';
    return 0;
}