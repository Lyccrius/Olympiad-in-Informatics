#include <iostream>

int t;

int w, d, h;
int a, b, f, g;

void mian() {
    std::cin >> w >> d >> h;
    std::cin >> a >> b >> f >> g;
    int cw = std::min(a + f, w + w - a - f);
    int cd = std::min(b + g, d + d - b - g);
    int dw = std::abs(a - f);
    int dd = std::abs(b - g);
    int ans = std::min(cw + dd, cd + dw) + h;
    std::cout << ans << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}