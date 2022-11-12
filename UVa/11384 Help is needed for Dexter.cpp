#include <cstdio>

const int maxn = 1e9 + 10;

int N;

int f(int n) {
    if (n == 1) return 1;
    return f(n / 2) + 1;
}

int main() {
    while (scanf("%d", &N) != EOF) {
        printf("%d\n", f(N));
    }
    return 0;
}