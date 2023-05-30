#include <iostream>
#include <map>
#include <cmath>

typedef long long lxl;
typedef std::map<lxl, lxl> mll;

lxl p, b, n;

lxl pow(lxl a, lxl b, lxl p) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % p;
        a = a * a % p;
        b = b / 2;
    }
    return ret;
}

lxl BSGS(lxl a, lxl b, lxl p) {
    mll hash;
    b %= p;
    lxl t = sqrt(p);
    for (lxl i = 0; i < t; i++) hash[b * pow(a, i, p) % p] = i;
    a = pow(a, t, p);
    if (!a) {
        if (b == 0) return 1;
        return -1;
    }
    for (int i = 1; i * t <= p; i++) {
        lxl x = pow(a, i, p);
        if (hash.find(x) != hash.end()) return i * t - hash[x];
    }
    return -1;
}

int main() {
    std::cin >> p >> b >> n;
    lxl ans = BSGS(b, n, p);
    if (ans == -1) {
        std::cout << "no solution" << '\n';
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}