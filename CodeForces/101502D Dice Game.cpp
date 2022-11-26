#include <cstdio>
#include <cstring>
#include <algorithm>

const int inf = 0x3f3f3f3f;
const int maxN = 1e4 + 10;

int T;
int n;
int f[maxN][10];

int main() {
    scanf("%d", &T);
    while (T--) {
        std::memset(f, inf, sizeof(f));
        f[0][1] = 0;
        scanf("%d", &n);
        for (int i = 0; i <= n; i++) {
            for (int top = 1; top <= 6; top++) {
                for (int last = 1; last <= 6; last++) {
                    if (top != last && top + last != 7) {
                        f[i + last][last] = std::min(f[i + last][last], f[i][top] + 1);
                    }
                }
            }
        }
        int res = inf;
        for (int i = 1; i <= 6; i++) res = std::min(res, f[n][i]);
        if (res < inf) printf("%d\n", res);
        else printf("-1\n");
    }
    return 0;
}