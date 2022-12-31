#include <cstdio>

const int maxN = 100;

int t;

int n, k;

void mian() {
    scanf("%d%d", &n, &k);
    int l = 1;
    int r = n;
    for (int i = 1; i <= n - k; i++) {
        if (i & 1) {
            printf("%d ", r);
            r--;
        } else {
            printf("%d ", l);
            l++;
        }
    }
    for (int i = l; i <= r; i++) printf("%d ", i);
    printf("\n");
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}