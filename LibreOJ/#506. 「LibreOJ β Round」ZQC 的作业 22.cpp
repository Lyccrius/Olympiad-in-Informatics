#include <iostream>
#include <bitset>
#include <cmath>

typedef long long lxl;

int tot = 1e8;
lxl p, q, n;
std::bitset<2147483647> vis;

lxl pow(lxl a, lxl b) {
    lxl ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % n;
        a = a * a % n;
        b = b / 2;
    }
    return ret;
}

int main() {
    std::cin >> p >> q >> n;
    int t = std::min((int) n, (int) (tot / log2(p)));
    for (lxl x = 0; x < t; x++) vis[pow(x, p) + q] = true;
    std::cout << vis.count() << '\n';
    return 0;
}