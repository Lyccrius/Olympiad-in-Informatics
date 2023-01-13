#include <cstdio>

const int maxN = 100 + 10;

int N, X;
int P[maxN];
int K;

int main() {
    scanf("%d%d", &N, &X);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
        if (P[i] == X) K = i;
    }
    printf("%d\n", K);
    return 0;
}