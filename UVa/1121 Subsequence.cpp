#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;

int N, S;
int A[maxN];
int B[maxN];

int main() {
    while (scanf("%d%d", &N, &S) != EOF) {
        B[0] = 0;
        for (int i = 1; i <= N; i++) {  
            scanf("%d", &A[i]);
            B[i] = B[i - 1] + A[i];
        }
        int ans = N + 1;
        int i = 1;
        for (int j = 1; j <= N; j++) {
            if (B[j] - B[i - 1] < S) continue;
            while (B[j] - B[i] >= S) i++;
            ans = std::min(ans, j - i + 1);
        }
        if (ans == N + 1) ans = 0;
        printf("%d\n", ans);
    }
    return 0;
}