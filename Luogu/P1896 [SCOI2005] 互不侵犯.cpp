#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

const int maxN = 9;

int N, K;
lxl F[maxN + 10][(1 << maxN) + 10][maxN + 10];
lxl ans;

int lenbit(lxl x) {
    int ret = 0;
    while (x) {
        if (x & 1) ret++;
        x >>= 1;
    }
    return ret;
}

bool check(lxl x, lxl y) {
    if (x & y) return false;
    if ((x << 1) & y) return false;
    if ((x >> 1) & y) return false;
    if ((x >> 1) & x) return false;
    if ((y >> 1) & y) return false;
    return true;
}

int main() {
    promote();
    std::cin >> N >> K;
    F[0][0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= (1 << N) - 1; j++) {
            int lj = lenbit(j);
            for (int k = 0; k <= K; k++) {
                if (lj > k) continue;
                for (int l = 0; l <= (1 << N) - 1; l++) {
                    if (!check(j, l)) continue;
                    F[i][j][k] += F[i - 1][l][k - lj];
                }
            }
        }
    }
    for (int i = 0; i <= (1 << N) - 1; i++) ans += F[N][i][K];
    std::cout << ans << '\n';
    return 0;
}