#include <cstdio>
#include <algorithm>

const int maxN = 5000 + 10;
const int maxM = 5000 + 10;

long long n, m;
long long square;
long long rectangle;

int main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) square += std::min(n - i + 1, m - j + 1);
    rectangle = n * (n + 1) / 2 * m * (m + 1) / 2;
    printf("%lld %lld\n", square, rectangle - square);
    return 0;
}