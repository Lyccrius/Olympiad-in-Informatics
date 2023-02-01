#include <iostream>

const int maxN = 100;

int N, A, B;

int main() {
    std::cin >> N >> A >> B;
    if ((B - A) % 2) std::cout << "Borys\n";
    else std::cout << "Alice\n";
    return 0;
}