#include <cstdio>

const int maxN = 1000;

int t;

int n;
char s[maxN + 10];

void mian() {
    scanf("%d", &n);
    if (n == 3) {
        printf("NO\n");
        return;
    }
    if (n & 1) {
        printf("YES\n");
        for (int i = 1; i <= n; i++) {
            if (i & 1) printf("%d ", n / 2 - 1);
            else printf("%d ", - n / 2);
        }
        printf("\n");
    } else {
        printf("YES\n");
        for (int i = 1; i <= n; i++) {
            if (i & 1) printf("%d ", 1);
            else printf("%d ", -1);
        }
        printf("\n");
    }
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}