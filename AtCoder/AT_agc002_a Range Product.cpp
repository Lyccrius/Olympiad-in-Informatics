#include <iostream>
#include <algorithm>

int a, b;
int x, y;

int main() {
    std::cin >> a >> b;
    x = std::max(a, b);
    y = std::min(a, b);
    if (x >= 0 && y <= 0) {
        std::cout << "Zero";
    } else if (y > 0) {
        std::cout << "Positive";
    } else {
        int t = x - y + 1;
        if (t & 1) {
            std::cout << "Negative";
        } else {
            std::cout << "Positive";
        }
    }
    return 0;
}