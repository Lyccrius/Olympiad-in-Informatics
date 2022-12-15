#include <cstdio>
#include <algorithm>
 
const int maxN = 2e5 + 10;
 
int t;
 
void mian() {
    long long n;
    int a[maxN];
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    long long p = 1;
    long long q = n;
    while (a[p] == a[p + 1] && p < n) p++;
    while (a[q] == a[q - 1] && q > 1) q--;
    if (a[1] != a[n]) printf("%lld\n", p * (n - q + 1) * 2);
    else printf("%lld\n", n * (n - 1));
    return;
}
 
int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}