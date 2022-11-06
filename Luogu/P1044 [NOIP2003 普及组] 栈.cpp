#include <cstdio>

const int maxn = 20;

int n;

int F[maxn][maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) F[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            F[i][j] = F[i - 1][j + 1] + F[i][j - 1];
        }
    }
    printf("%d\n", F[n][0]);
    return 0;
}