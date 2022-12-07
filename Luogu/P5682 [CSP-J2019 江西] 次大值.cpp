#include <cstdio>
#include <algorithm>

const int maxN = 2e5 + 10;

int n;
int a[maxN];
int b[maxN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    int tot = std::unique(a + 1, a + n + 1) - a - 1;
    if (tot == 1) printf("%d\n", -1);
    else printf("%d\n", std::max(a[tot - 2], a[tot] % a[tot - 1]));
    return 0;
}