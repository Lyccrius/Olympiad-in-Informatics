#include <iostream>
#include <cstring>

const int maxN = 1000;
const int maxW = 1000000;
const int maxA = 10;
const int maxB = 30;

int n, W;
int x, y;
int m[maxB + 10];
int w[maxB + 10][maxN + 10];
int v[maxB + 10][maxN + 10];
int f[maxB + 10][maxN * maxA + 10];
int g[maxB + 10][maxN * maxA + 10];

void split(int W, int V) {
    int b = 0;
    while ((W & 1) == 0) {
        W /= 2;
        b += 1;
    }
    m[b]++;
    w[b][m[b]] = W;
    v[b][m[b]] = V;
    return;
}

void mian() {
    memset(m, 0, sizeof(m));
    memset(f, 0, sizeof(f));
    memset(g, 0xcf, sizeof(g));
    for (int i = 1; i <= n; i++) std::cin >> x >> y, split(x, y);
    for (int b = 0; b <= maxB; b++) {
        for (int i = 1; i <= m[b]; i++) {
            for (int j = maxA * n; j >= w[b][i]; j--) {
                f[b][j] = std::max(f[b][j], f[b][j - w[b][i]] + v[b][i]);
            }
        }
    }
    g[maxB][0] = 0;
    for (int b = maxB; b >= 1; b--) {
        int t = (W >> (b - 1)) & 1;
        g[b - 1][t] = 0;
        for (int i = 0; i <= maxA * n; i++) {
            if (2 * i + t > maxA * n) continue;
            for (int j = 0; j <= 2 * i + t; j++) {
                g[b - 1][2 * i + t - j] = std::max(g[b - 1][2 * i + t - j], g[b][i] + f[b - 1][j]);
            }
        }
    }
    std::cout << g[0][0] << '\n';
    return;
}

int main() {
    while (std::cin >> n >> W && ~n && ~W) mian();
    return 0;
}