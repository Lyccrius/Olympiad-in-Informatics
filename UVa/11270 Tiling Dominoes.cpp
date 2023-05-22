#include <iostream>
#include <cstring>

typedef long long lxl;

const int maxM = 10;

int n, m;
int cur;
int p[maxM + 10];
lxl f[2][(1 << maxM) + 10];

void mian() {
    if (n < m) std::swap(n, m);
    memset(f, 0, sizeof(f));
    cur = 0;
    f[0][(1 << m) - 1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cur ^= 1;
            memset(f[cur], 0, sizeof(f[cur]));
            for (int k = 0; k < (1 << m); k++) {
                if (k & p[j]) f[cur][k ^ p[j]] += f[cur ^ 1][k];
                if (i != 1 && (k & p[j]) == 0) f[cur][k ^ p[j]] += f[cur ^ 1][k];
                if (j != 1 && (k & p[j - 1]) == 0 && (k & p[j])) f[cur][k ^ p[j - 1]] += f[cur ^ 1][k];
            }
        }
    }
    printf("%lld\n", f[cur][(1 << m) - 1]);
    return;
}

int main() {
    for (int j = 1; j <= maxM; j++) p[j] = 1 << (j - 1);
    while (scanf("%d%d", &n, &m) != EOF) mian();
    return 0;
}