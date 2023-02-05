#include <iostream>
#include <algorithm>
#include <vector>

typedef long long lxl;

const lxl maxN = 2e5;

lxl t;
lxl n;
lxl a[maxN + 10];

void mian() {
    lxl cnt = 0;
    lxl sum = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) if (a[i] < 0) cnt++, a[i] = -a[i];
    for (int i = 1; i <= n; i++) sum += a[i];
    std::sort(a + 1, a + n + 1);
    if (cnt & 1) sum -= 2 * a[1];
    std::cout << sum << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}