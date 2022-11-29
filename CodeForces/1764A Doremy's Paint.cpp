#include <cstdio>

const int maxN = 1e5 + 10;

int t;
int n;
int a[maxN];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        printf("%d %d\n", 1, n);
    }
    return 0;
}