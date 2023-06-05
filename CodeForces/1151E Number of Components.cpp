#include <iostream>

typedef long long lxl;

const int maxN = 1e5;

int n;
int a[maxN + 10];
lxl v;
lxl e;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) v += 1ll * a[i] * (n - a[i] + 1);
    for (int i = 1; i < n; i++) e += 1ll * std::min(a[i], a[i + 1]) * (n - std::max(a[i], a[i + 1]) + 1);
    std::cout << v - e << '\n';
    return 0;
}