#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

lxl n, k;

lxl G(lxl n, lxl k) {
    lxl ret = n * k;
    for (int l = 1, r; l <= n; l = r + 1) {
        if (k / l) r = std::min(k / (k / l), n);
        else r = n;
        ret -= (k / l) * (l + r) * (r - l + 1) / 2;
    }
    return ret;
}

int main() {
    std::cin >> n >> k;
    std::cout << G(n, k);
    return 0;
}