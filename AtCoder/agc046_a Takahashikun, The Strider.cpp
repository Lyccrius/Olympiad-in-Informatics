#include <iostream>

int X;

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    std::cin >> X;
    std::cout << 360 / gcd(360, X);
    return 0;
}