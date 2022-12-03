#include <cstdio>

const int maxN = 25 + 10;

int n;
bool f[maxN][maxN * maxN];

int main() {
    scanf("%d", &n);
    int m = n * (n - 1) / 2;
    int cnt = 0;
    for (int i = 1; i <= n; i++) f[i][0] = true;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) for (int k = 1; k <= n - i;k++) if (f[i][j]) f[i + k][j + i * k] = true;
    for (int i = 0; i <= m; i++) if (f[n][i]) cnt++;
    printf("%d\n", cnt);
    return 0;
}