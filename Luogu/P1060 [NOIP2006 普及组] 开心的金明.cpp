#include <cstdio>
#include <cstring>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 3e4 + 10;
const int maxM = 25 + 10;

int n, m;
int v[maxM];
int p[maxM];
int f[maxN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) scanf("%d%d", &v[i], &p[i]);
    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= v[i]; j--) {
            f[j] = std::max(f[j], f[j - v[i]] + v[i] * p[i]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = std::max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}