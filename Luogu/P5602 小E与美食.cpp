#include <iostream>
#include <algorithm>
#include <iomanip>

typedef long double dbl;

const int maxN = 3e5;

int n;
int a[maxN + 10];
dbl res;
dbl ans;

int main() {
    std::cout << std::setiosflags(std::ios::fixed);
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    std::reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        res += a[i];
        ans = std::max(ans, res * res / i);
    }
    std::cout << std::setprecision(8) << ans << '\n';
    return 0;
}