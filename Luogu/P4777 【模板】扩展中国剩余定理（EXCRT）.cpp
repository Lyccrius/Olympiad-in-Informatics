#include <iostream>

typedef long long lxl;
typedef __int128 i28;

const int maxN = 1e5;

int n;
lxl a[maxN + 10], b[maxN + 10];
lxl x, M;

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

void merge(lxl a, lxl m) {
    lxl p, q;
    lxl d = a - x;
    lxl g = exgcd(M, p, m, q);
    p = ((i28) p * d / g) % (m / g);
    p = ((i28) p + (m / g)) % (m / g);
    x += (i28) p * M;
    M = (i28) M * m / g;
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
    x = b[1];
    M = a[1];
    for (int i = 2; i <= n; i++) merge(b[i], a[i]);
    std::cout << x << '\n';
    return 0;
}