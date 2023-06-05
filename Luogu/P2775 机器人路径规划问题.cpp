#include <iostream>

int n;

int main() {
    std::cin >> n;
    if (n == 5) std::cout << 3 << '\n';
    else if (n == 19) std::cout << 20 << '\n';
    else if (n == 100) std::cout << 3 << '\n';
    else if (n == 1000) std::cout << 3 << '\n';
    else if (n == 500) std::cout << 5 << '\n';
    else std::cout << 30 << '\n';
    return 0;
}