#include <iostream>
#include <algorithm>

const int maxN = 1e5;
const int maxA = 2000;

int n;
int a[maxN + 10];
int c[maxA + 10];
int ans = maxN * maxA;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) c[a[i]]++;
    for (int x = 1; x <= maxA; x++) {
        int res = 0;
        for (int ai = 1; ai <= maxA; ai++) res += c[ai] * (ai / x + ai % x);
        ans = std::min(ans, res);
    }
    std::cout << ans << '\n';
    return 0;
}