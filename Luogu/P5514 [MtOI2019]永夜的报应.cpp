#include <cstdio>

const int maxN = 1e6 + 10;

int n;
int a[maxN];

int main() {
    scanf("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        ans ^= a[i];
    }
    printf("%d\n", ans);
    return 0;
}