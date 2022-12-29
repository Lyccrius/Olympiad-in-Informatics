#include <cstdio>

const int maxM = 3e5 + 10;

int m;
long long a[maxM], b[maxM];
long long A[70], B[70];
long long F[70];

int main() {
    F[1] = 1;
    F[2] = 1;
    for (int i = 3; i <= 60; i++) F[i] = F[i - 1] + F[i - 2];
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld", &a[i], &b[i]);
        a[i]--;
        b[i]--;
        for (int j = 60; j >= 1; j--) {
            A[j] = a[i] / F[j];
            a[i] = a[i] % F[j];
        }
        for (int j = 60; j >= 1; j--) {
            B[j] = b[i] / F[j];
            b[i] = b[i] % F[j];
        }
        long long ans = 1;
        for (int j = 1; j <= 60; j++) {
            if (A[j + 1] != B[j + 1]) break;
            ans += F[j] * A[j];
        }
        printf("%lld\n", ans);
    }
    return 0;
}