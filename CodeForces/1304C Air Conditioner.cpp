#include <iostream>
#include <algorithm>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 100;

int q;
int n, m;
int t[maxN + 10], l[maxN + 10], r[maxN + 10];

void mian() {
    std::cin >> n >> m; int L = m, R = m;
    for (int i = 1; i <= n; i++) std::cin >> t[i] >> l[i] >> r[i];
    for (int i = 1; i <= n; i++) {
        L -= t[i] - t[i - 1];
        R += t[i] - t[i - 1];
        if (L > r[i] || R < l[i]) {
            std::cout << "NO" << '\n';
            return;
        }
        L = std::max(L, l[i]);
        R = std::min(R, r[i]);
    }
    std::cout << "YES" << '\n';
    return;
}

int main() {
    std::cin >> q;
    while (q--) mian();
    return 0;
}