#include <cstdio>
#include <cstring>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 250 * 250 + 10;

int T;
int N, p, q, x;

int main() {
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        int num[maxN];
        int S[maxN];
        int g[maxN];
        int d[maxN];
        int n = 0;
        std::memset(num, 0, sizeof(num));
        std::memset(g, inf, sizeof(g));
        scanf("%d%d%d", &N, &p, &q);
        for (int i = 1; i <= p + 1; i++) {
            scanf("%d", &x);
            num[x] = i;
        }
        for (int i = 0; i < q + 1; i++) {
            scanf("%d", &x);
            if (num[x]) S[n++] = num[x];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int k = std::lower_bound(g + 1, g + n + 1, S[i]) - g;
            d[i] = k;
            g[k] = S[i];
            ans = std::max(ans, d[i]);
        }
        printf("Case %d: %d\n", kase, ans);
    }
    return 0;
}