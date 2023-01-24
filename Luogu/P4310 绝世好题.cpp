#include <iostream>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1e5;

int n;
int a[maxN + 10];
int f[30 + 10];
int res, ans;

int main() {
    std::fill(f, f + 30, 0);
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) { res = 0;
        for (int p = 0; p <= 30; p++) if ((a[i] >> p) & 1) res = std::max(res, f[p] + 1);
        for (int p = 0; p <= 30; p++) if ((a[i] >> p) & 1) f[p] = std::max(res, f[p]);
        ans = std::max(ans, res);
    }
    std::cout << ans << '\n';
    return 0;
}