#include <iostream>

const int maxN = 400;
const int mod = 998244353;

int n, k;
int a[maxN + 10][maxN + 10];
int ans = 1;

int main() {
    std::cin >> n >> k;
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            std::cin >> a[u][v];
        }
    }
    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            for (int w = 1; w <= n; w++) {
                if (u == v) continue;
                if (u == w) continue;
                if (v == w) continue;
                if (a[u][v] == a[u][w] + a[w][v]) {
                    ans = 1ll * ans * (k - a[u][v] + 1) % mod;
                    break;
                }
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}