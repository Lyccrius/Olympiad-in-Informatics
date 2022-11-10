#include <cstdio>
#include <algorithm>

const int maxn = 1e5 + 10;

int N;
int A[maxn];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
    std::sort(A + 1, A + N + 1);
    for (int i = 1; i <= N; i++) printf("%d ", A[i]);
    return 0;
}