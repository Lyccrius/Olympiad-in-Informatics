#include <iostream>

typedef long long lxl;

const int maxN = 10;

lxl N;
lxl M = 1;
lxl a[maxN + 10];
lxl n[maxN + 10];
lxl m[maxN + 10];
lxl x, y, t;

lxl exgcd(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl ret = exgcd(b, y, a % b, x);
    y -= a / b * x;
    return ret;
}

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> n[i] >> a[i];
    for (int i = 1; i <= N; i++) M *= n[i];
    for (int i = 1; i <= N; i++) {
        m[i] = M / n[i];
        exgcd(m[i], t, n[i], y);
        t = (t + n[i]) % n[i];
        x = (x + a[i] * m[i] % M * t % M) % M;
    }
    std::cout << x << '\n';
    return 0;
}