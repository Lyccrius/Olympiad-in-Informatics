#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 10;
const int maxM = 100;
const int inf = 1e9;

int n, m;
int a[maxM + 10][maxN + 10];
int f[(1 << maxN) + 10];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            std::cin >> a[i][j];
        }
    }
    std::fill(f + 1, f + (1 << maxN), inf);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 1; j <= m; j++) {
            int t = i;
            for (int k = 1; k <= n; k++) {
                if ((a[j][k] == 1 && !((1 << (k - 1)) & i)) ||
                    (a[j][k] == -1 && ((1 << (k - 1)) & i))) {
                    t ^= (1 << (k - 1));
                }
            }
            f[t] = std::min(f[t], f[i] + 1);
        }
        //printf("f[%d] = %d\n", i, f[i]);
    }
    if (f[(1 << n) - 1] == inf) f[(1 << n) - 1] = -1;
    std::cout << f[(1 << n) - 1] << '\n';
    return 0;
}