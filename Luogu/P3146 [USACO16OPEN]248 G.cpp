#include <cstdio>
#include <algorithm>

const int maxN = 248 + 10;

int N;
int A[maxN];
int F[maxN][maxN];
int res;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) F[i][i] = A[i];
    for (int len = 1; len <= N; len++) for (int i = 1; i + len - 1 <= N; i++) {
        int j = i + len - 1;
        for (int k = i; k < j; k++) if (F[i][k] == F[k + 1][j]) {
            F[i][j] = std::max(F[i][j], F[i][k] + 1);
            res = std::max(res, F[i][j]);
        }
    }
    printf("%d\n", res);
    return 0;
}