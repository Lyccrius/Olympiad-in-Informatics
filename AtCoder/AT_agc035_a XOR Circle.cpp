#include <iostream>

const int maxN = 1e5;

int N;
int a[maxN + 10];
int c[32];

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= 31; j++) {
            if (a[i] & (1 << j)) {
                c[j]++;
            }
        }
    }
    for (int i = 0; i <= 31; i++) {
        if (c[i] & 1) {
            std::cout << "No" << '\n';
            return 0;
        }
    }
    std::cout << "Yes" << '\n';
    return 0;
}