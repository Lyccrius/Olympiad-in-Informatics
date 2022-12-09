#include <cstdio>

const int maxN = 100 + 10;

int n;
char s[maxN];
int res;

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i < n; i++) if (s[i] == 'V' && s[i + 1] == 'K') res++, s[i] = 'v', s[i + 1] = 'k';
    for (int i = 1; i < n; i++) if (s[i] == s[i + 1] && (s[i] == 'V' || s[i] == 'K')) {res++; break;}
    printf("%d\n", res);
    return 0;
}