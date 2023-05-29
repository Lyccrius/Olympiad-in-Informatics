#include <iostream>

typedef long long lxl;

const int maxN = 50;
const int maxP = 50;

int n;
lxl a[maxN + 10];
lxl b[maxP + 10];

void insert(lxl x) {
    for (int p = maxP; p >= 0; p--) {
        if ((x & (1ll << p)) == 0) continue;
        if (!b[p]) {
            b[p] = x;
            return;
        }
        x ^= b[p];
    }
    return;
}

lxl query() {
    lxl ret = 0;
    for (int p = maxP; p >= 0; p--) ret = std::max(ret, ret ^ b[p]);
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i], insert(a[i]);
    std::cout << query() << '\n';
    return 0;
}