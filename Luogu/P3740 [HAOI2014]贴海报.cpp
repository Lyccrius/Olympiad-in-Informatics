#include <cstdio>

const int maxN = 1e7;
const int maxM = 1e3;

int N, M;
int A[maxM + 10], B[maxM + 10];
int electoral[maxN + 10];
int cnt[maxM + 10];
int ans;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &A[i], &B[i]);
        for (int j = A[i]; j <= B[i]; j++) electoral[j] = i;
    }
    for (int i = 1; i <= N; i++) cnt[electoral[i]]++;
    for (int i = 1; i <= M; i++) if (cnt[i]) ans++;
    printf("%d\n", ans);
    return 0;
}