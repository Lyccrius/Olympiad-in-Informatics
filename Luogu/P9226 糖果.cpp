#include <iostream>

int n, k;

int main() {
    std::cin >> n >> k;
    std::cout << k - (n % k);
    return 0;
}