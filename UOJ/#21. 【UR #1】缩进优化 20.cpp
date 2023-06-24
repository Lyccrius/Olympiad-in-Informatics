#include <iostream>
#include <algorithm>

const int maxN = 1e3;
const int maxA = 2000;

int n;
int a[maxN + 10];
int ans = maxN * maxA;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int x = 1; x <= maxA; x++) {
        int res = 0;
        for (int i = 1; i <= n; i++) res += a[i] / x + a[i] % x;
        ans = std::min(ans, res);
    }
    std::cout << ans << '\n';
    return 0;
}