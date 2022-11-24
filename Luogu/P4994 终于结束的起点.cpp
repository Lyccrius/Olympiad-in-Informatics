#include <cstdio>

const int maxN = 1e7 + 10;

int m;
int f[maxN];

long long fib(long long i) {
    if (i < maxN && f[i]) return f[i];
    else return f[i] = (fib(i - 1) + fib(i - 2)) % m;
}

int main() {
	f[1] = 1;
	f[2] = 1;
    scanf("%lld", &m);
    long long n = 1;
    while (fib(n) != 0 || fib(n + 1) != 1) n++;
    printf("%lld\n", n);
    return 0;
}