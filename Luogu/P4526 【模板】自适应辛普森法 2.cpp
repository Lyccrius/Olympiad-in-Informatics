#include <iostream>
#include <iomanip>
#include <cmath>

typedef double dbl;

const dbl eps = 1e-6;

dbl a;

dbl f(dbl x) {
    return pow(x, a / x - x);
}

dbl simpson(dbl l, dbl r) {
    dbl mid = (l + r) / 2;
    return (f(l) + 4 * f(mid) + f(r)) * (r - l) / 6;
}

dbl asr(dbl l, dbl r, dbl eps, dbl res) {
    dbl mid = (l + r) / 2;
    dbl tl = simpson(l, mid);
    dbl tr = simpson(mid, r);
    if (std::abs(tl + tr - res) < 15.0 * eps) return tl + tr + (tl + tr - res) / 15;
    return asr(l, mid, eps / 2, tl) + asr(mid, r, eps / 2, tr);
}

dbl asr(dbl l, dbl r) {
    return asr(l, r, eps, simpson(l, r));
}

int main() {
    std::cin >> a;
    if (a < 0) {
        std::cout << "orz" << '\n';
        return 0;
    }
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(5) << asr(eps, 15.0) << '\n';
    return 0;
}