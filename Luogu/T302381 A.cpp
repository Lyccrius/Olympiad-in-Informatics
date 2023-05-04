#include <iostream>
#include <iomanip>

typedef double dbl;

const dbl inf = 1e10;

int n, m;
dbl x, y;
dbl l, r;

int main() {
    l = -inf;
    r = inf;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> x >> y;
        if (x == 0) {
            if (0 <= y && y <= 2 * m) {
                std::cout << "0.000" << '\n';
                return 0;
            }
        }
        if (x < 0) {
            l = std::max(l, 0.5 * x - (m - 0.5 * y) * y / x);
        }
        if (x > 0) {
            r = std::min(r, 0.5 * x - (m - 0.5 * y) * y / x);
        }
    }
    if (l <= -inf || inf <= r) {
        std::cout << "Infinity" << '\n';
    } else {
        std::cout << std::setiosflags(std::ios::fixed);
        std::cout << std::setprecision(3) << r - l << '\n';
    }
    return 0;
}