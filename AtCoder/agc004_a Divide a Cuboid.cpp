#include <iostream>

typedef long long lxl;

lxl A, B, C;

int main() {
    std::cin >> A >> B >> C;
    if (A % 2 == 0 || B % 2 == 0 || C % 2 == 0) {
        std::cout << 0;
    } else {
        lxl AB = A * B;
        lxl AC = A * C;
        lxl BC = B * C;
        std::cout << std::min(std::min(AB, AC), BC);
    }
    return 0;
}