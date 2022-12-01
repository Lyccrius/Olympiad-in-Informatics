#include <cstdio>

const int maxN = 50 + 10;

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        int n, m;
        char a[maxN];
        char b[maxN];
        scanf("%d%d", &n, &m);
        scanf("%s", a + 1);
        scanf("%s", b + 1);
        bool ok = true;
        for (int i = n, j = m; j > 1; i--, j--) if (a[i] != b[j]) {ok = false; break;}
        bool found = false;
        for (int i = 1; i <= n - m + 1; i++) if (a[i] == b[1]) {found = true; break;}
        if (ok && found) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}