#include <iostream>

typedef long long lxl;

int t;
lxl n;

void mian() {
    std::cin >> n;
    if (n < 7) {
        std::cout << -1 << '\n';
        return;
    }
    lxl ans = 0;
    lxl cnt = 0;
    lxl p = 60;
    while (cnt < 3) {
        if (ans + (1ll << p) <= n) {
            lxl gap = n - (ans + (1ll << p));
            if (cnt == 2) ans += (1ll << p), cnt++;
            if (cnt == 1 && gap >= 1) ans += (1ll << p), cnt++;
            if (cnt == 0 && gap >= 3) ans += (1ll << p), cnt++;
        }
        p--;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}