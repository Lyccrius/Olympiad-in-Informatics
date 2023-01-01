#include <cstdio>

int T;
long long L, R;
char ch;
long long x;
long long res;

void mian() {
    scanf(" %c%lld", &ch, &x);
    res = 0;
    if (ch == 'L') {
        res -= L;
        res -= x * (L + R);
        if (x & 1) res += R;
        else res += L;
    } else {
        res += R;
        res += x * (L + R);
        if (x & 1) res -= L;
        else res -= R;
    }
    printf("%lld\n", res);
    return;
}

int main() {
    scanf("%d", &T);
    scanf("%lld%lld", &L, &R);
    while (T--) mian();
    return 0;
}