#include <cstdio>
#include <algorithm>

const int maxN = 500 + 10;
const int inf = 1e9 + 10;

int n;
int C[maxN];
int F[maxN][maxN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &C[i]);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) F[i][j] = inf;
    for (int i = 1; i <= n; i++) F[i][i] = 1;
    for (int i = 1; i < n; i++) if (C[i] == C[i + 1]) F[i][i + 1] = 1; else F[i][i + 1] = 2;
    for (int len = 3; len <= n; len++) for (int i = 1; i + len - 1 <= n; i++) {
        int j = i + len - 1;
        if (C[i] == C[j]) F[i][j] = F[i + 1][j - 1];
        for (int k = i; k < j; k++) F[i][j] = std::min(F[i][j], F[i][k] + F[k + 1][j]);
    }
    printf("%d\n", F[1][n]);
    return 0;
}