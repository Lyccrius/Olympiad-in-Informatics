#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;
const int maxM = 1e4;

int n, m;
int t[maxM + 10], x[maxM + 10], y[maxM + 10];
int f[maxM + 10];
int ans;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> t[i] >> x[i] >> y[i];
    for (int i = 1; i <= m; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]) <= t[i] - t[j]) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
        ans = std::max(ans, f[i]);
    }
    std::cout << ans << '\n';
    return 0;
}