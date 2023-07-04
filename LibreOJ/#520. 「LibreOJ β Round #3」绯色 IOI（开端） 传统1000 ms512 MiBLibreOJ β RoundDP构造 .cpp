#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;

int n;
lxl w[maxN + 10];
lxl ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    std::sort(w + 1, w + n + 1);
    for (int i = 1; i + 2 <= n; i++) ans += (w[i + 2] - w[i]) * (w[i + 2] - w[i]);
    ans += (w[2] - w[1]) * (w[2] - w[1]);
    ans += (w[n] - w[n - 1]) * (w[n] - w[n - 1]);
    std::cout << ans << '\n';
    return 0;
}