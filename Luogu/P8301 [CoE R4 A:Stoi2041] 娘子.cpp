#include <cstdio>
#include <cmath>

const int maxN = 1e3;

int n;
int a[maxN + 10];
int b[maxN + 10];
int cnt;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%1d", &a[i]), cnt += a[i];
    for (int i = 1; i <= n; i++) scanf("%1d", &b[i]), cnt -= b[i];
    printf("%d\n", std::abs(cnt));
    return 0;
}