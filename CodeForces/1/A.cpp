#include <bits/stdc++.h>

using namespace std;

int n, m;
int a;

int main() {
    scanf("%d%d%d", &n, &m, &a);

    long long x = ceil((double)n / a);
    long long y = ceil((double)m / a);
    long long ans = x * y;

    printf("%lld\n", ans);

    return 0;
}