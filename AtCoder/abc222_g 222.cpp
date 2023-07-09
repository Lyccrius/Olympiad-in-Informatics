#include <iostream>
#include <map>
#include <cmath>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;
typedef std::map<lxl, lxl> mll;

int t;
lxl k;

lxl pow(lxl a, lxl b, lxl p) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b = b / 2;
    }
    return ret;
}

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

lxl exGCD(lxl a, lxl &x, lxl b, lxl &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    lxl d = exGCD(b, y, a % b, x);
    y -= a / b * x;
    return d;
}

lxl BSGS(lxl a, lxl b, lxl p) {
    b = (b % p + p) % p;
    //if (1 % p == b % p) return 0;
    mll hash;
    lxl t = sqrt(p) + 1;
    lxl w = 1;
    for (int i = 0; i < t; i++) hash[b * w % p] = i, w = w * a % p;
    a = pow(a, t, p);
    for (int i = 1; i <= t; i++) {
        lxl x = pow(a, i, p);
        if (hash.find(x) != hash.end()) return i * t - hash[x];
    }
    return -1;
}

lxl exBSGS(lxl a, lxl b, lxl p) {
    b = (b % p + p) % p;
    //if (1 % p == b % p) return 0;
    lxl x, y;
    lxl d = exGCD(a, x, p, y);
    if (d > 1) {
        if (b % d) return -1;
        exGCD(a / d, x, p / d, y);
        return exBSGS(a, b / d * x, p / d) + 1;
    }
    return BSGS(a, b, p);
}

void mian() {
    std::cin >> k;
    if (k % 2 == 0) k /= 2;
    if (gcd(k * 9, 10) != 1) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << exBSGS(10, 1, 9 * k) << '\n';
    return;
}

int main() {
    promote();
    std::cin >> t;
    while (t--) mian();
    return 0;
}