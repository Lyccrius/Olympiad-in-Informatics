#include <cstdio>

long long a, b, c;
long long f[30][30][30];

long long w(long a, long b, long long c) {
    long long res;
    if (0 <= a && a < 30 && 0 <= b && b < 30 && 0 <= c && c < 30 && f[a][b][c]) return f[a][b][c];
    if (a <= 0 || b <= 0 || c <= 0) res = 1;
    else if (a > 20 || b > 20 || c > 20) res = w(20, 20, 20);
    else if (a < b && b < c) res = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    else res = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
    if (0 <= a && a < 30 && 0 <= b && b < 30 && 0 <= c && c < 30) f[a][b][c] = res;
    return res;
}

int main() {
    while (scanf("%lld%lld%lld", &a, &b, &c) && (a != -1 || b != -1 || c != -1)) {
        long long ans = w(a, b, c);
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, ans);
    }
    printf("\n");
    return 0;
}