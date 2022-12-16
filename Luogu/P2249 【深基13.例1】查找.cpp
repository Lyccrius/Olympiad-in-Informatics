#include <cstdio>
#include <algorithm>

const int maxN = 1e6 + 10;

int n, m;
int a[maxN];
int q;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &q);
        int res = std::lower_bound(a + 1, a + n + 1, q) - a;
        if (a[res] != q) res = -1;
        printf("%d ", res);
    }
    return 0;
}