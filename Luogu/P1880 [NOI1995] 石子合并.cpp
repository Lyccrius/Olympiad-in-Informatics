#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;

int N;
int a[maxN * 2 + 10];
int b[maxN * 2 + 10];
int f[maxN * 2 + 10][maxN * 2 + 10];
int g[maxN * 2 + 10][maxN * 2 + 10];

int main() {
    promote();
    std::memset(f, 0x3f, sizeof(f));
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i], a[N + i] = a[i];
    for (int i = 1; i <= 2 * N; i++) b[i] = b[i - 1] + a[i];
    for (int i = 1; i <= 2 * N; i++) f[i][i] = 0;
    for (int i = 1; i <= 2 * N; i++) g[i][i] = 0;
    for (int len = 2; len <= N; len++) {
        for (int i = 1; i <= 2 * N; i++) {
            int j = i + len - 1;
            if (j > 2 * N) break;
            for (int k = i; k < j; k++) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
                g[i][j] = std::max(g[i][j], g[i][k] + g[k + 1][j]);
            }
            f[i][j] += b[j] - b[i - 1];
            g[i][j] += b[j] - b[i - 1];
            //printf("f[%d][%d] = %d, g[%d][%d] = %d\n", i, j, f[i][j], i, j, g[i][j]);
        }
    }
    for (int i = 1; i <= N; i++) {
        int j = i + N - 1;
        f[0][0] = std::min(f[0][0], f[i][j]);
        g[0][0] = std::max(g[0][0], g[i][j]);
    }
    std::cout << f[0][0] << '\n' << g[0][0];
    return 0;
}