#include <iostream>

const int maxN = 1e5;

int n, p;
int h[maxN + 10];
int m[maxN + 10];

int main() {
    m[0] = 1;
    std::cin >> n >> p;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    for (int i = 1; i <= n; i++) m[i] = 1ll * m[i - 1] * 26 % p;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            if ((1ll * h[i] * 26 % p + p - 1ll * m[n] * j % p + j) % p == h[i % n + 1]) {
                std::cout << (char) ('a' + j);
            }
        }
    }
    return 0;
}