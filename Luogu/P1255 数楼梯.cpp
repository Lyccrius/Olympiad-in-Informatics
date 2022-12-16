#include <cstdio>

const int maxN = 5000 + 10;

int N;
unsigned long long F[maxN];

int main() {
    scanf("%d", &N);
    F[0] = 1;
    for (int i = 0; i < N; i++) {
        F[i + 1] += F[i];
        F[i + 2] += F[i];
    }
    printf("%llu\n", F[N]);
    return 0;
}