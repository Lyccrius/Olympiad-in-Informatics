#include <iostream>
#include <algorithm>
#include <cmath>

typedef long long lxl;

const int maxN = 2e5;
const int maxQ = 2e5;

int n;
lxl v[maxN + 10];
int q;
lxl t[maxQ + 10];
lxl pre[maxN + 10];
int top;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> v[i];
    std::cin >> q;
    for (int i = 1; i <= q; i++) std::cin >> t[i];
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + v[i];
    for (int i = 1; i <= n; i++) top = std::max(top, (int) std::ceil(1.0 * pre[i] / i));
    for (int i = 1; i <= q; i++) {
        if (t[i] < top) {
            std::cout << -1 << '\n';
        } else {
            std::cout << std::ceil(1.0 * pre[n] / t[i]) << '\n';
        }
    }
    return 0;
}