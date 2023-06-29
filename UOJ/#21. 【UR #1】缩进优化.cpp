#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e6;
const int maxA = 1e6;

int n;
int a[maxN + 10];
lxl b[maxA + 10];
int c[maxA + 10];
lxl sum;
lxl ans = 1ll * maxN * maxA;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) sum += a[i];
    for (int i = 1; i <= n; i++) c[a[i]]++;
    for (int i = 1; i <= maxA; i++) c[i] += c[i - 1];
    for (int x = 1; x <= maxA; x++) {
        for (int t = 1; t <= maxA / x; t++) {
            b[x] += 1ll * t * (c[std::min(maxA, (t + 1) * x - 1)] - c[t * x - 1]);
        }
    }
    for (int x = 1; x <= maxA; x++) ans = std::min(ans, sum - b[x] * (x - 1));
    std::cout << ans << '\n';
    return 0;
}