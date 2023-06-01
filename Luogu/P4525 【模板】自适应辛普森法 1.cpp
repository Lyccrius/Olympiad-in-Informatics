#include <iostream>
#include <iomanip>

typedef double dbl;

const dbl eps = 1e-6;

dbl a, b, c, d, l, r;

dbl f(dbl x) {
    return (c * x + d) / (a * x + b);
}

dbl simpson(dbl l, dbl r) {
    dbl mid = (l + r) / 2;
    return (f(l) + 4.0 * f(mid) + f(r)) * (r - l) / 6;
}

dbl asr(dbl l, dbl r, dbl eps, dbl res) {
    dbl mid = (l + r) / 2;
    dbl sl = simpson(l, mid);
    dbl sr = simpson(mid, r);
    if (std::abs(sl + sr - res) <= 15.0 * eps) return sl + sr + (sl + sr - res) / 15;
    return asr(l, mid, eps / 2, sl) + asr(mid, r, eps / 2, sr); 
}

dbl asr(dbl l, dbl r) {
    return asr(l, r, eps, simpson(l, r));
}

int main() {
    std::cin >> a >> b >> c >> d >> l >> r;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(6) << asr(l, r) << '\n';
    return 0;
}