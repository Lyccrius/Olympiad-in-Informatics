#include <iostream>

typedef char chr;
typedef long long lxl;

int T;
lxl n, m, k, p;

lxl log(lxl x) {
    if (x == 1) return 0;
    return log(x / 2) + 1;
}

lxl pow(lxl a, lxl b) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

lxl mul(lxl a, lxl b) {
    lxl ret = 0;
    a = a % p;
    while (b) {
        if (b & 1) ret = (ret + a) % p;
        a = a * 2 % p;
        b = b / 2;
    }
    return ret;
}

lxl calc(lxl x, lxl y, lxl n, lxl m, lxl base) {
    if (x >= n) return 0;
    if (y >= m) return 0;
    //base = x + y;
    //if (x == y) base = 0;
    lxl ret = 0;
    lxl dx = log(n - x);
    lxl dy = log(m - y);
    lxl lx = pow(2, dx);
    lxl ly = pow(2, dy);
    lxl l, r;
    lxl tmp;
    if (lx < ly) {
        l = ((base - k) % p + p) % p;
        r = ((base - k + ly - 1) % p + p) % p;
        if (base < k) l = 0;
        if (base + ly > k) {
            if ((l & 1) == (r & 1)) {
                ret = mul((l + r) / 2 % p, ((r - l + 1) % p + p) % p);
            } else {
                ret = mul((l + r) % p, ((r - l + 1) / 2 % p + p) % p);
            }
            ret = ret * lx % p;
        }
        tmp = ret;
        ret = (ret + calc(x + lx, y, n, y + ly, base)) % p;
        ret = (ret + calc(x, y + ly, n, m, base + ly)) % p;
    } else if (lx > ly) {
        l = ((base - k) % p + p) % p;
        r = ((base - k + lx - 1) % p + p) % p;
        if (base < k) l = 0;
        if (base + lx > k) {
            if ((l & 1) == (r & 1)) {
                ret = mul((l + r) / 2 % p, ((r - l + 1) % p + p) % p);
            } else {
                ret = mul((l + r) % p, ((r - l + 1) / 2 % p + p) % p);
            }
            ret = ret * ly % p;
        }
        tmp = ret;
        ret = (ret + calc(x + lx, y, n, m, base + lx)) % p;
        ret = (ret + calc(x, y + ly, x + lx, m, base)) % p;
    } else {
        l = ((base - k) % p + p) % p;
        r = ((base - k + ly - 1) % p + p) % p;
        if (base < k) l = 0;
        if (base + ly > k) {
            if ((l & 1) == (r & 1)) {
                ret = mul((l + r) / 2 % p, ((r - l + 1) % p + p) % p);
            } else {
                ret = mul((l + r) % p, ((r - l + 1) / 2 % p + p) % p);
            }
            ret = ret * lx % p;
        }
        tmp = ret;
        ret = (ret + calc(x + lx, y, n, y + ly, base + lx)) % p;
        ret = (ret + calc(x, y + ly, x + lx, m, base + ly)) % p;
        ret = (ret + calc(x + lx, y + ly, n, m, base)) % p;
    }
    //ret = (ret + calc(x + lx, y, n, y + ly, (base + lx)));
    //ret = (ret + calc(x, y + ly, x + lx, m, (base + ly)));
    //ret = (ret - calc(x + len, y + len, (base + len)) + p);
    //ret = (ret + calc(x + lx, y + ly, n, m, (base + lx + ly)));
    //ret = (ret) + p;
    //printf("calc(%lld, %lld, %lld, %lld) %lld, %lld, base on %lld, [%lld, %lld] = %lld\n", x, y, n, m, lx, ly, base, l, r, tmp);
    return ret;
}

void mian() {
    std::cin >> n >> m >> k >> p;
    std::cout << (calc(0, 0, n, m, 0) % p + p) % p << '\n';
    //std::cout << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}