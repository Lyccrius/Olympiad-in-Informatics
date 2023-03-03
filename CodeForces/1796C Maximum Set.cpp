#include <iostream>
#include <vector>

const int maxN = 1e6;
const int logN = 20;
const int mod = 998244353;

int log[maxN + 10];

int t;
int l, r;

void init() {
    for (int i = 2; i <= maxN; i++) {
        log[i] = log[i / 2] + 1;
    }
    return;
}

int f[logN + 5][maxN + 10];
int g[logN + 5][maxN + 10];

void mian() {
    std::cin >> l >> r;
    int tot = log[r / l] + 1;
    for (int i = 1; i <= tot; i++) {
        for (int j = l; j <= r; j++) {
            f[i][j] = 0;
        }
    }
    for (int j = l; j <= r; j++) f[1][j] = 1;
    for (int i = 1; i <= tot; i++) {
        for (int j = l; j <= r; j++) {
            for (int k = 2; j * k <= r; k++) {
                f[i + 1][j * k] = (f[i + 1][j * k] + f[i][j]) % mod;
            }
        }
    }
    int ans = 0;
    for (int j = l; j <= r; j++) ans += f[tot][j];
    std::cout << tot << ' ' << ans << '\n';
    return;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}