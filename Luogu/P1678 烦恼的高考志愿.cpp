#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxN = 1e5 + 10;

int n, m;
int lu[maxN];
int gu[maxN];
long long res;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &lu[i]);
    for (int i = 1; i <= m; i++) scanf("%d", &gu[i]);
    std::sort(lu + 1, lu + n + 1);
    for (int i = 1; i <= m; i++) {
        int cho = std::lower_bound(lu + 1, lu + n + 1, gu[i]) - lu;
        if (cho == n + 1) {
            res += gu[i] - lu[n];
            continue;
        }
        if (cho == 1) {
            res += lu[1] - gu[i];
            continue;
        }
        int difL = std::abs(gu[i] - lu[cho - 1]);
        int difR = std::abs(lu[cho] - gu[i]);
        res += std::min(difL, difR);
    }
    printf("%lld\n", res);
    return 0;
}