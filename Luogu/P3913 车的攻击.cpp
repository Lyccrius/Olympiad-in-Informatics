#include <cstdio>
#include <algorithm>

const int maxN = 1e9 + 10;
const int maxK = 1e6 + 10;

long long N, K;
int R[maxK], C[maxK];

int main() {
    scanf("%lld%lld", &N, &K);
    for (int i = 1; i <= K; i++) scanf("%d%d", &R[i], &C[i]);
    std::sort(R + 1, R + K + 1);
    std::sort(C + 1, C + K + 1);
    long long r = std::unique(R + 1, R + K + 1) - R - 1;
    long long c = std::unique(C + 1, C + K + 1) - C - 1;
    printf("%lld\n", r * N + c * N - r * c);
    return 0;
}