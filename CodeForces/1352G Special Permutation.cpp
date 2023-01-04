#include <cstdio>

int t;

int n;

void mian() {
    scanf("%d", &n);
    if (n <= 3) {
        printf("%d\n", -1);
        return;
    }
    for (int i = (n - 1) / 2 * 2 + 1; i >= 1; i -= 2) printf("%d ", i);
    for (int i = 4; i >= 2; i -= 2) printf("%d ", i);
    for (int i = 6; i <= n; i += 2) printf("%d ", i);
    printf("\n");
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}