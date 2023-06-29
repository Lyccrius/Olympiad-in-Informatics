#include <iostream>

typedef char chr;

const int maxN = 1e5;

int n, p;
int h[maxN + 10];
int m[maxN + 10];
chr s[maxN + 10];

int main() {
    m[0] = 1;
    std::cin >> n >> p;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    for (int i = 1; i <= n; i++) m[i] = 1ll * m[i - 1] * 26 % p;
    if (m[n] == 1) {
        for (int i = 1; i <= n; i++) {
            s[n - i + 1] = 'a' + h[1] % 26;
            h[1] /= 26;
            std::cout << (s + 1);
        }
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 26; j++) {
                if ((1ll * h[i] * 26 % p + p - 1ll * m[n] * j % p + j) % p == h[i % n + 1]) {
                    std::cout << (chr) ('a' + j);
                }
            }
        }
    }
    return 0;
}