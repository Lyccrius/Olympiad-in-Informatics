#include <iostream>

typedef long long lxl;

const int maxN = 1000;

lxl f[maxN + 10][5][2];
lxl ans[maxN + 10];
int kase;
int L;

int main() {
    for (int k = 0; k < 2; k++) {
        f[1][0][k] = 1;
        for (int i = 2; i <= maxN; i++) {
            for (int j = 0; j < 5; j++) {
                f[i][j][k] = f[i - 1][j][k];
                if (j > 0) f[i][j][k] += f[i - 1][j - 1][k];
            }
        }
    }
    for (int i = 1; i <= maxN; i++) {
        if (i < 4) continue;
        if (i & 1) continue;
        int R = (i + 4) / 2;
        ans[i] = f[R][3][0] + f[R][4][1] + f[R][4][0];
    }
    while (std::cin >> L && L) {
        std::cout << "Case " << ++kase << ": " << ans[L] << '\n';
    }
    return 0;
}