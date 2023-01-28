#include <iostream>

const int maxN = 50;

int t;
int n, s, r;

void mian() {
    std::cin >> n >> s >> r;
    int m = s - r;
    while (s >= m && n >= 1 && s - m >= n - 1) {
        s -= m;
        n -= 1;
        std::cout << m << ' ';
    }
    if (!n) {
        printf("\n");
        return;
    }
    m = s - n + 1;
    std::cout << m << ' ';
    s -= m;
    n--;
    for (int i = 1; i <= n; i++) std::cout << 1 << ' ';
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}