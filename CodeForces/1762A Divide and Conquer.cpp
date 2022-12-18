#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 50 + 10;
const int inf = 1e9 + 10;

int t;
int n;
int a[maxN];
int f[maxN][maxN][2];

void mian() {
    std::memset(f, inf, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) if (a[i] % 2) {
        f[i][i][1] = 0;
        f[i][i][0] = 0;
        int x = a[i];
        while (x % 2) {
            x /= 2;
            f[i][i][0]++;
        }
    } else {
        f[i][i][0] = 0;
        f[i][i][1] = 0;
        int x = a[i];
        while (x % 2 == 0 && x) {
            x /= 2;
            f[i][i][1]++;
        }
        if (x == 0) f[i][i][1] = -1;
    }
    for (int len = 2; len <= n; len++) for (int i = 1; i + len - 1 <= n; i++) {
        int j = i + len - 1;
        for (int k = i; k < j; k++) {
            f[i][j][0] = std::min(f[i][j][0], f[i][k][0] + f[k + 1][j][0]);
            if (f[i][k][1] != -1) f[i][j][1] = std::min(f[i][j][1], f[i][k][1] + f[k + 1][j][0]);
            if (f[k + 1][j][1] != -1) f[i][j][1] = std::min(f[i][j][1], f[i][k][0] + f[k + 1][j][1]);
            if (f[i][k][1] != -1 && f[k + 1][j][1] != -1) f[i][j][0] = std::min(f[i][j][0], f[i][k][1] + f[k + 1][j][1]);
        }
    }
    printf("%d\n", f[1][n][0]);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}