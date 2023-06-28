#include <iostream>
#include <cmath>

typedef long long lxl;
typedef __int128 i28;

lxl n, m, k;

bool check(lxl s) {
    lxl a = std::min((lxl) sqrt(s), n);
    lxl b = s / a;
    lxl c = s - a * b;
    i28 t = (i28) s * (s - 1) / 2;
    t -= (a - 1) * b;
    t -= (b - 1) * a;
    t -= std::max((lxl) 0, c + c - 1);
    return t <= k;
}

int main() {
    std::cin >> n >> m >> k;
    if (n > m) std::swap(n, m);
    lxl l = 0;
    lxl r = n * m;
    while (l < r) {
        lxl mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    std::cout << l << '\n';
    return 0;
}