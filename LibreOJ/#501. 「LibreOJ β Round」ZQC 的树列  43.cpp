#include <iostream>
#include <cmath>

typedef long long lxl;

lxl k;

int main() {
    std::cin >> k;
    int t = log2(k);
    if (k == (int) pow(2, t)) {
        std::cout << t + 2 << '\n';
        for (int i = 1; i <= t + 2; i++) std::cout << i << ' ';
        std::cout << '\n';
    } else if (k + 1 == (int) pow(2, t + 1)) {
        std::cout << t + 1<< '\n';
        for (int i = 1; i <= t + 1; i++) std::cout << 0 << ' ';
        std::cout << '\n';
    } else {
        std::cout << "qnq" << '\n';
    }
    return 0;
}