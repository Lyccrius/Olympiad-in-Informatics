#include <cstdio>

const int maxN = 50;

int t;

int n;

void mian() {
    scanf("%d", &n);
    int l = 0;
    int r = n * n + 1;
    int a[maxN * maxN + 10];
    for (int i = 1; i <= n * n; i++) {
        if (i & 1) a[i] = ++l;
        else a[i] = --r;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i & 1) printf("%d ", a[(i - 1) * n + j]);
            else printf("%d ", a[i * n - j + 1]);
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