#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long lxl;

const int maxN = 100;
const int maxA = 10;
const int maxB = 30;

int n, W;
int w[maxN + 10];
int v[maxN + 10];
int m[maxB + 10];
int w2[maxB + 5][maxN + 10];
int v2[maxB + 5][maxN + 10];
lxl f[maxB + 10][maxN * 10 + 10];
lxl g[maxB + 10][maxN * 10 + 10];

void init() {
    std::memset(m, 0, sizeof(m));
    std::memset(w2, 0, sizeof(w2));
    std::memset(v2, 0, sizeof(v2));
    std::memset(f, 0, sizeof(f));
    std::memset(g, 0xcf, sizeof(g));
    return;
}

void split() {
    for (int i = 1; i <= n; i++) {
        int b = 0;
        while (!(w[i] & 1)) {
            w[i] >>= 1;
            b++;
        }
        m[b]++;
        w2[b][m[b]] = w[i];
        v2[b][m[b]] = v[i];
    }
    return;
}

void merge() {
    g[maxB][0] = 0;
    for (int b = maxB; b >= 1; b--) {
        g[b - 1][0] = 0;
        g[b - 1][W >> (b - 1) & 1] = 0;
        for (int j = 0; j <= maxA * n; j++) {
            for (int k = 0; k <= std::min(maxA * n, 2 * j + (W >> (b - 1) & 1)); k++) {
                int l = std::min(maxA * n, 2 * j + (W >> (b - 1) & 1) - k);
                g[b - 1][l] = std::max(g[b - 1][l], g[b][j] + f[b - 1][k]);
            }
        }
    }
    for (int j = 1; j <= maxA * n; j++) g[0][0] = std::max(g[0][0], g[0][j]);
    return;
}

void mian() {
    init();
    for (int i = 1; i <= n; i++) std::cin >> w[i] >> v[i];
    split();
    for (int b = 0; b <= maxB; b++) {
        for (int i = 1; i <= m[b]; i++) {
            for (int j = maxA * n; j >= w2[b][i]; j--) {
                f[b][j] = std::max(f[b][j], f[b][j - w2[b][i]] + v2[b][i]);
            }
        }
    }
    merge();
    std::cout << g[0][0] << '\n';
    return;
}

int main() {
    while (std::cin >> n >> W && ~n && ~W) mian();
    return 0;
}