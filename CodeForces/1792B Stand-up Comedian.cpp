#include <iostream>

int t;
int a1, a2, a3, a4;
int ans;

void mian() {
    std::cin >> a1 >> a2 >> a3 >> a4;
    ans = 0;
    ans += a1;
    ans += std::min(a2, a3) * 2;
    ans += std::min(a1 + 1, std::max(a2, a3) - std::min(a2, a3) + a4);
    if (a1 == 0) ans = 1;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}