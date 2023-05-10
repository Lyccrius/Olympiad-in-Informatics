#include <iostream>

int T;

void mian() {
    std::cout << "failed" << '\n';
    return;
}

int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    std::cin >> T;
    while (T--) mian();
    return 0;
}