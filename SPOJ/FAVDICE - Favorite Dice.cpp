#include <cstdio>

typedef unsigned long long lxl;

lxl n;
lxl num, den;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

lxl lcm(lxl a, lxl b) {
    return a * b / gcd(a, b);
}

void approx() {
    lxl t = gcd(num, den);
    num /= t;
    den /= t;
    return;
}

void plus(lxl n, lxl d) {
    if (num == 0) {
        num = n;
        den = d;
        return;
    }
    lxl t = gcd(den, d);
    num = num * (d / t);
    n = n * (den / t);
    num = num + n;
    den = den * (d / t);
    approx();
    return;
}

lxl popcount(lxl x) {
    lxl ret = 0;
    while (x) {
        ret++;
        x /= 10;
    }
    return ret;
}

void output() {
    if (num % den == 0) {
        printf("%lld\n", num / den);
        return;
    }
    lxl t = num / den;
    num = num % den;
    lxl n = popcount(t);
    lxl d = popcount(den);
    for (lxl i = 1; i <= n; i++) printf(" ");
    printf("%lld\n", num);
    printf("%lld", t);
    for (lxl i = 1; i <= d; i++) printf("-");
    printf("\n");
    for (lxl i = 1; i <= n; i++) printf(" ");
    printf("%lld\n", den);
    return;
}
/*
void mian() {
    num = 0;
    den = 0;
    for (lxl i = 1; i <= n; i++) plus(1, i);
    num = num * n;
    approx();
    output();
    return;
}
*/
void mian() {
    scanf("%lld", &n);
    double res = 0;
    for (int i = 1; i <= n; i++) res += (double) 1 / i;
    res = res * n;
    printf("%.2lf\n", res);
    return;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) mian();
}