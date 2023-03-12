#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e7;

lxl n, x, y;
lxl f[maxN + 10];

int main() {
    std::cin >> n >> x >> y;
    for (lxl i = 1; i <= n; i++) {
        if (i & 1) {
            f[i] = std::min(f[i - 1] + x, f[(i + 1) / 2] + y + x);
        } else {
            f[i] = std::min(f[i - 1] + x, f[i / 2] + y);
        }
    }
    std::cout << f[n];
    return 0;
}