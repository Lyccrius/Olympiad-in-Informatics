#include <cstdio>

const int maxN = 100 + 10;

int t;
int n;
int a[maxN];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        bool ok = true;
        for (int i = 2; i <= n; i++) if (a[i] % a[1]) {ok = false; break;}
        if (ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}