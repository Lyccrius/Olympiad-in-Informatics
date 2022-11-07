#include <cstdio>
#include <cmath>
 
int t;
int n;
int a;
long long s1, s2;
 
int main() {
    scanf("%d", &t);
    while (t--) {
        s1 = 0;
        s2 = 0;
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &a);
            if (a > 0) s1 += a;
            else s2 -= a;
        }
        long long ans = std::abs(s1 - s2);
        printf("%lld\n", ans);
    }
    return 0;
}