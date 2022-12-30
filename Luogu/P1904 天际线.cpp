#include <cstdio>
#include <algorithm>

const int maxN = 5000;

int N, M;
int L[maxN + 10], H[maxN + 10], R[maxN + 10];
int Range[maxN * 2 + 10];
int Genoa[maxN * 2 + 10];

int main() {
    N++;
    while (scanf("%d%d%d", &L[N], &H[N], &R[N]) != EOF) N++;
    N--;
    for (int i = 1; i <= N; i++) Range[i] = L[i], Range[N + i] = R[i];
    std::sort(Range + 1, Range + 2 * N + 1);
    M = std::unique(Range + 1, Range + 2 * N + 1) - Range - 1;
    for (int i = 1; i <= N; i++) {
        L[i] = std::lower_bound(Range + 1, Range + M + 1, L[i]) - Range;
        R[i] = std::lower_bound(Range + 1, Range + M + 1, R[i]) - Range;
        for (int j = L[i]; j < R[i]; j++) Genoa[j] = std::max(Genoa[j], H[i]);
    }
    int last = 0;
    for (int i = 1; i <= M; i++) {
        if (last != Genoa[i]) {
            last = Genoa[i];
            printf("%d %d ", Range[i], Genoa[i]);
        }
    }
    printf("\n");
    return 0;
}