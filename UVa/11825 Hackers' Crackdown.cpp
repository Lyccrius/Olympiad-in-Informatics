#include <iostream>

const int maxN = 16;
const int maxM = 16;

int kase;
int n;
int m[maxN + 10];
int a[maxN + 10][maxM + 10];
int p[maxN + 10];
int c[(1 << maxN) + 10];
int f[(1 << maxN) + 10];

void mian() {
    for (int i = 0; i < n; i++) {
        std::cin >> m[i];
        p[i] = 0;
        p[i] ^= (1 << i);
        for (int j = 0; j < m[i]; j++) {
            std::cin >> a[i][j];
            p[i] ^= (1 << a[i][j]);
        }
    }
    for (int s = 0; s < (1 << n); s++) {
        c[s] = 0;
        for (int i = 0; i < n; i++) {
            if (s & (1 << i)) {
                c[s] |= p[i];
            }
        }
    }
    for (int s = 1; s < (1 << n); s++) {
        f[s] = 0;
        for (int t = s; t; t = (t - 1) & s) {
            if (c[t] == (1 << n) - 1) {
                f[s] = std::max(f[s], f[s ^ t] + 1);
            }
        }
    }
    std::cout << "Case " << ++kase << ": " << f[(1 << n) - 1] << '\n';
    return;
}

int main() {
    while (std::cin >> n && n) mian();
    return 0;
}