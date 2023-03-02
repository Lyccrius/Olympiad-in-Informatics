#include <iostream>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const lxl maxN = 1e16;
const lxl mod = 1e9 + 7;

int t;
lxl n;
lxl pre[50];

lxl gcd(lxl a, lxl b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

lxl lcm(lxl a, lxl b) {
    return a * b / gcd(a, b);
}

void init() {
    lxl i = 1;
    pre[1] = 1;
    while (pre[i] <= maxN) {
        i++;
        pre[i] = lcm(i, pre[i - 1]);
    }
    return;
}

void mian() {
    std::cin >> n;
    lxl ans = 0;
    lxl i = 1;
    while (pre[i] <= n) {
        i++;
        ans = (ans + i * (n / pre[i - 1] - n / pre[i])) % mod;
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    init();
    std::cin >> t;
    while (t--) mian();
    return 0;
}