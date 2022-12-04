#include<cstdio>

int n, a, b;

unsigned long long calc(int n, int x) {
    unsigned long long res = 1;
    for (int i = 1; i <= x; ++i) {
        res *= n - i + 1;
        res /= i;
    }
    return res;
}

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    printf("%llu\n", calc(a + n, n) * calc(b + n, n));
    return 0;
}