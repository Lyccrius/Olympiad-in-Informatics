#include <cstdio>
#include <cstring>

const int maxn = 1e6 + 10;

char s1[maxn];
char s2[maxn];

int n, m;
int next[maxn];

int main() {
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    n = std::strlen(s1 + 1);
    m = std::strlen(s2 + 1);
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && s2[i] != s2[j + 1]) j = next[j];
        if (s2[j + 1] == s2[i]) j++;
        next[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s2[j + 1] != s1[i]) j = next[j];
        if (s2[j + 1] == s1[i]) j++;
        if (j == m) {
            printf("%d\n", i - m + 1);
            j = next[j];
        }
    }
    for (int i = 1; i <= m; i++) printf("%d ", next[i]);
    return 0;
}