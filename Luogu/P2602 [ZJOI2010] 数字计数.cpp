#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<int> vic;

lxl a, b;
vic bits;
lxl p[20];
lxl v[20];
lxl f[20];

lxl pow(lxl a, lxl b) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a;
        a = a * a;
        b = b / 2;
    }
    return ret;
}

lxl DFS(int u, int dig, int zer, int lim) {
    if (u < 0) return 0;
    if (!lim && !zer && v[u]) return f[u];
    lxl ret = 0;
    int tot = lim ? bits[u] : 9;
    for (int i = 0; i <= tot; i++) {
        if (i == 0 && zer) {
            ret += DFS(u - 1, dig, true, lim && i == tot);
        } else if (i == dig) {
            if (lim && i == tot) {
                ret += p[u - 1] + 1 + DFS(u - 1, dig, false, true);
            } else {
                ret += pow(10, u) + DFS(u - 1, dig, false, false);
            }
        } else {
            ret += DFS(u - 1, dig, false, lim && i == tot);
        }
    }
    if ((!zer) && (!lim)) {
        v[u] = true;
        f[u] = ret;
    }
    return ret;
}

lxl calc(lxl n, lxl dig) {
    bits.clear();
    std::fill(p, p + sizeof(p) / 8, 0);
    std::fill(v, v + sizeof(v) / 8, 0);
    std::fill(f, f + sizeof(f) / 8, 0);
    while (n) {
        bits.push_back(n % 10);
        n /= 10;
        p[bits.size() - 1] = p[bits.size() - 2] + 1ll * bits[bits.size() - 1] * pow(10, bits.size() - 1);
    }
    return DFS(bits.size() - 1, dig, true, true);
}

int main() {
    std::cin >> a >> b;
    for (int i = 0; i <= 9; i++) std::cout << calc(b, i) - calc(a - 1, i) << ' ';
    return 0;
}