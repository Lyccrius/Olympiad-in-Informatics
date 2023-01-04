#include <cstdio>
#include <cmath>

const int inf = 2e9;

long long n;

int main() {
    scanf("%lld", &n);
    long long l = 1;
    long long r = inf;
    while (l < r) {
        long long mid = (l + r) >> 1;
        if (mid * std::log10(1.0 * mid) + 1 >= n) r = mid;
        else l = mid + 1;
    }
    printf("%lld\n", l);
    return 0;
}