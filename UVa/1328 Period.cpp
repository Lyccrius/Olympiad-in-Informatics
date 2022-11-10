#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 10;

int t;
int n;
char s[maxn];
int next[maxn];
int f[maxn];

void KMP() {
    next[1] = 0;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j > 0 && s[i] != s[j + 1]) j = next[j];
        if (s[i] == s[j + 1]) j++;
        next[i] = j;
    }
    for (int i = 2; i <= n; i++) {
        if (i % (i - next[i]) == 0 && i / (i - next[i]) > 1) {
            printf("%d %d\n", i, i / (i - next[i]));
        }
    }
    return;
}

int main() {
    while (scanf("%d", &n) && n) {
        t++;
        printf("Test case #%d\n", t);
        scanf("%s", s + 1);
        KMP();
        printf("\n");
    }
    return 0;
}