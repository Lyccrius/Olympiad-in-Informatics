#include <iostream>
#include <map>
#include <cmath>

typedef long long lxl;
typedef std::map<lxl, lxl> mll;

lxl x, z, k;

lxl pow(lxl a, lxl b, lxl p) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b = b / 2;
    }
    return ret;
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
    mll hash;
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    lxl t = sqrt(p);
    lxl w = 1;
    for (int i = 0; i < t; i++) hash[b * w % p] = i, w = w * a % p;
    a = pow(a, t, p);
    for (int i = 1; (i - 1) * t < p; i++) {
        lxl x = pow(a, i, p);
        if (hash.find(x) != hash.end()) return t * i - hash[x];
    }
    return -1;
}

lxl exBSGS(lxl a, lxl b, lxl p) {
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
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
    lxl ans = exBSGS(x, k, z);
    if (~ans) std::cout << ans << '\n';
    else std::cout << "No Solution" << '\n';
    return;
}

int main() {
    while (std::cin >> x >> z >> k && (x || z || k)) mian();
    return 0;
}