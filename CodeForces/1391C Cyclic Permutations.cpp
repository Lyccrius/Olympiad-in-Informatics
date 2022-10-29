#include <bits/stdc++.h>

const int mod = 1e9 + 7;

int main() {
    int n;
    scanf("%d", &n);

    long long ans = 1;
    long long pow = 1;
    for (int i = 1; i <= n; i++) {
        ans = ans * i % mod;
    }
    for (int i = 1; i < n; i++) {
        pow = pow * 2 % mod;
    }

    printf("%lld\n", (ans - pow + mod) % mod );

    return 0;
}