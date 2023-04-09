#include <iostream>

int T;
int n;

void mian() {
    std::cin >> n;
    std::cout << n / 2 << '\n';
    for (int i = 2; i <= n; i += 2) std::cout << i << ' ';
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}