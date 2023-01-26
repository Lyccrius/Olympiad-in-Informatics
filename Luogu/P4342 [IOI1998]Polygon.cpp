#include <iostream>
#include <vector>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 50;

int n;
char opt[2 * maxN + 10];
int val[2 * maxN + 10];
int f[2 * maxN + 10][2 * maxN + 10];
int g[2 * maxN + 10][2 * maxN + 10];
int ans;
std::vector<int> vic;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> opt[i] >> val[i];
    for (int i = 1; i <= n; i++) opt[n + i] = opt[i], val[n + i] = val[i];
    std::memset(f, 0x3f, sizeof(f));
    std::memset(g, 0xcf, sizeof(g));
    for (int i = 1; i <= 2 * n; i++) f[i][i] = val[i], g[i][i] = val[i];
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n * 2; i++) {
            int j = i + len - 1;
            if (j > 2 * n) break;
            for (int k = i; k < j; k++) {
                if (opt[k + 1] == 't') {
                    f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
                    g[i][j] = std::max(g[i][j], g[i][k] + g[k + 1][j]);
                } else {
                    f[i][j] = std::min(f[i][j], f[i][k] * f[k + 1][j]);
                    f[i][j] = std::min(f[i][j], f[i][k] * g[k + 1][j]);
                    f[i][j] = std::min(f[i][j], g[i][k] * f[k + 1][j]);
                    f[i][j] = std::min(f[i][j], g[i][k] * g[k + 1][j]);
                    g[i][j] = std::max(g[i][j], f[i][k] * f[k + 1][j]);
                    g[i][j] = std::max(g[i][j], f[i][k] * g[k + 1][j]);
                    g[i][j] = std::max(g[i][j], g[i][k] * f[k + 1][j]);
                    g[i][j] = std::max(g[i][j], g[i][k] * g[k + 1][j]);
                }
            }
            //printf("f[%d][%d] = %d, g[%d][%d] = %d\n", i, j, f[i][j], i, j, g[i][j]);
        }
    }
    ans = 0xcfcfcfcf;
    for (int i = 1; i <= n; i++) {
        int j = i + n - 1;
        if (ans < g[i][j]) {
            ans = g[i][j];
            vic.clear();
        }
        if (ans == g[i][j]) {
            vic.push_back(i);
        }
    }
    std::cout << ans << '\n';
    for (auto i : vic) std::cout << i << ' ';
    return 0;
}