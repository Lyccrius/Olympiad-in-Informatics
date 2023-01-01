#include <cstdio>

const int maxN = 1e5;
const int maxM = 1e6;

int n, m;
int f[maxM + 10];
int a[maxN + 10];
int tot = 0;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%1d", &f[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) if (f[a[i] - tot]) tot++;
    printf("%d\n", tot);
    return 0;
}