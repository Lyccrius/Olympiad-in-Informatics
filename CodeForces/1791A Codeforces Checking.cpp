#include <iostream>

int t;

char c;

void mian() {
    std::cin >> c;
    if (c == 'c' || c == 'o' || c == 'd' || c == 'e' || c == 'f' || c == 'r' || c == 's') std::cout << "YES\n";
    else std::cout << "NO\n";
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}