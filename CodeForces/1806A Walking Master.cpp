#include <iostream>

int t;
int a, b, c, d;

void mian() {
    std::cin >> a >> b >> c >> d;
    int dx = c - a;
    int dy = d - b;
    if (dy < 0 || dy < dx) {
        std::cout << - 1 << '\n';
        return;
    }
    std::cout << dy + dy - dx << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}