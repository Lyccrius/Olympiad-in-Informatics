#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int N, W;
int X[maxN], B[maxN];
long long pre[maxN];

int main() {
    scanf("%d%d", &N, &W);
    int maxX = 0;
    long long ans = 0;
    for (int i = 1; i <= N; i++) scanf("%d%d", &X[i], &B[i]), maxX = std::max(maxX, X[i]);
    for (int i = 1; i <= N; i++) pre[X[i]] += B[i];
    for (int i = 1; i <= maxX; i++) pre[i] += pre[i - 1];
    for (int i = 0; i + W <= maxX; i++) ans = std::max(ans, pre[i + W] - pre[i]);
    printf("%lld\n", ans);
    return 0;
}