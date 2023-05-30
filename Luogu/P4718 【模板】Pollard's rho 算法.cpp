#include <iostream>

typedef __int128 i28;
typedef long long lxl;
typedef bool bol;

int t;
lxl n;
lxl mac;

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

lxl pow(lxl a, lxl b, lxl p) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = (i28) ret * a % p;
        a = (i28) a * a % p;
        b = b / 2;
    }
    return ret;
}

bol MillerRabin(lxl p) {
    if (p < 2) return false;
    if (p == 2) return true;
    if (p == 3) return true;
    lxl d = p - 1;
    lxl r = 0;
    while ((d & 1) == 0) {
        r++;
        d /= 2;
    }
    for (lxl k = 0; k < 10; k++) {
        lxl a = rand() % (p - 2) + 2;
        lxl x = pow(a, d, p);
        if (x == 1) continue;
        if (x == p - 1) continue;
        for (int i = 0; i < r - 1; i++) {
            x = (i28) x * x % p;
            if (x == p - 1) break;
        }
        if (x != p - 1) return false;
    }
    return true;
}

lxl PollarRho(lxl x) {
    lxl s = 0;
    lxl t = 0;
    lxl c = 1ll * rand() % (x - 1) + 1;
    int step = 0;
    int goal = 1;
    lxl val = 1;
    while (true) {
        step = 1;
        while (step <= goal) {
            t = ((i28) t * t + c) % x;
            val = (i28) val * std::abs(t - s) % x;
            if (step % 127 == 0) {
                lxl d = gcd(val, x);
                if (d > 1) return d;
            }
            step++;
        }
        lxl d = gcd(val, x);
        if (d > 1) return d;
        goal *= 2;
        s = t;
        val = 1;
    }
}

void fac(lxl x) {
    if (x <= mac || x < 2) return;
    if (MillerRabin(x)) {
        mac = std::max(mac, x);
        return;
    }
    lxl p = x;
    while (x <= p) p = PollarRho(x);
    while (x % p == 0) x /= p;
    fac(x);
    fac(p);
    return;
}

void mian() {
    std::cin >> n;
    mac = 0;
    fac(n);
    if (mac == n) {
        std::cout << "Prime" << '\n';
    } else {
        std::cout << mac << '\n';
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}