#include <cstdio>

int t;
int m;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        int base = 1;
        while (base * 10 <= m) base *= 10;
        printf("%d\n", m - base);
    }
    return 0;
}