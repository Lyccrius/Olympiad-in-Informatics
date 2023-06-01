#include <iostream>

const int maxN = 5e4;

int n, d, t;

int main() {
    std::cin >> n >> d;
    //t = (n - 1);
    if (d * 2 >= n) {
        std::cout << "No" << '\n';
        return 0;
    }
    std::cout << "Yes" << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            std::cout << i + 1 << ' ' << (i + j + 1) % n + 1 << '\n';
        }
    }
    return 0;
}