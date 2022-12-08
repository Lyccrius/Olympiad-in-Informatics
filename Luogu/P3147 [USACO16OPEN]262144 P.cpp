#include <cstdio>
#include <algorithm>

const int maxN = 262144 + 10;
const int maxA = 58 + 10;

int N;
int A[maxN];
int F[maxA][maxN];
int res;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) F[A[i]][i] = i + 1;
    for (int i = 2; i <= 58; i++) for (int j = 1; j <= N; j++) {
        if (!F[i][j]) F[i][j] = F[i - 1][F[i - 1][j]];
        if (F[i][j]) res = i;
    }
    printf("%d\n", res);
    return 0;
}