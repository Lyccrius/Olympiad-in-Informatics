#include <cstdio>
#include <algorithm>

const int maxN = 100 + 10;

int t;
int n, x;
int h[maxN * 2];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &x);
        for (int i = 1; i <= n * 2; i++) scanf("%d", &h[i]);
        std::sort(h + 1, h + n * 2 + 1);
        bool ok = true;
        for (int i = 1; i <= n; i++) if (h[i + n] - h[i] < x) {ok = false; break;}
        if (ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}