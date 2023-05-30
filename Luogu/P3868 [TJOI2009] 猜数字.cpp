#include <iostream>

typedef long long lxl;
typedef __int128 i28;

const int maxK = 10;

int k;
lxl a[maxK + 10];
lxl b[maxK + 10];
lxl n;
lxl m[maxK + 10];
lxl t[maxK + 10];
lxl B = 1;

lxl exgcd(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl d = exgcd(b, y, a % b, x);
    y -= a / b * x;
    return d;
}

lxl inv(lxl a, lxl b) {
    lxl x, y;
    exgcd(a, x, b, y);
    return (x + b) % b;
}

int main() {
    std::cin >> k;
    for (int i = 1; i <= k; i++) std::cin >> a[i];
    for (int i = 1; i <= k; i++) std::cin >> b[i];
    for (int i = 1; i <= k; i++) B *= b[i];
    for (int i = 1; i <= k; i++) {
        m[i] = B / b[i];
        t[i] = inv(m[i], b[i]);
        n = ((i28) n + (i28) m[i] * t[i] % B * a[i] % B) % B;
    }
    std::cout << n << '\n';
    return 0;
}