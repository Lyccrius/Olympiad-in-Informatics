#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 5000;
const int maxS = 50;
const int maxT = 100;
const int maxF = 100;
const lxl inf = 1e18 + 10;

int n;
int s;
int t[maxN + 10], f[maxN + 10];
lxl pt[maxN + 10];
lxl pf[maxN + 10];
lxl dp[maxN + 10];

int main() {
    std::cin >> n;
    std::cin >> s;
    for (int i = 1; i <= n; i++) std::cin >> t[i] >> f[i];
    for (int i = 1; i <= n; i++) pt[i] = pt[i - 1] + t[i];
    for (int i = 1; i <= n; i++) pf[i] = pf[i - 1] + f[i];
    for (int i = 1; i <= n; i++) dp[i] = inf; dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = std::min(dp[i], dp[j] + 1ll * pt[i] * (pf[i] - pf[j]) + 1ll * s * (pf[n] - pf[j]));
        }
    }
    std::cout << dp[n];
    return 0;
}