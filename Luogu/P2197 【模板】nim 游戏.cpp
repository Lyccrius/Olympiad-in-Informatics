#include <iostream>

const int maxN = 1e4;

int T;
int n;
int a[maxN + 10];
int b;

void mian() {
    b = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b ^= a[i];
    if (b) {
        std::cout << "Yes" << '\n';
    } else {
        std::cout << "No" << '\n';
    }
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}