#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 50 + 10;

int t;
int n, m;
char s[maxN];
int a[maxN * 2];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i] = std::min(a[i], m - a[i] + 1);
        for (int i = 1; i <= m; i++) s[i] = 'B';
        s[m + 1] = '\0';
        std::sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) if (s[a[i]] == 'B') s[a[i]] = 'A'; else if(s[m - a[i] + 1] == 'B') s[m - a[i] + 1] = 'A';
        printf("%s\n", s + 1);
    }
    return 0;
}