#include <cstdio>
#include <algorithm>

const int maxN = 2e5;
const int inf = 1e9 + 10;

int N;
int A[maxN + 10];
int B[maxN + 10];
int F[maxN + 10];
int ans;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= N; i++) B[A[i]] = i;
    for (int i = 1; i <= N; i++) F[i] = 1;
    for (int i = 1; i <= N; i++) if (B[A[i] - 1] < i) F[i] = F[B[A[i] - 1]] + 1, ans = std::max(ans, F[i]);
    printf("%d\n", N - ans);
    return 0;
}