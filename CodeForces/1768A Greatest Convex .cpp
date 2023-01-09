#include <cstdio>

int t;

int k;

void mian() {
    scanf("%d", &k);
    printf("%d\n", k - 1);
    return;
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}