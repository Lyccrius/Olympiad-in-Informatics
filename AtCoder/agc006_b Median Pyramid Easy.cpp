#include <iostream>

const int maxN = 1e5;

int N, x;
int a[2 * maxN + 10];
int cur = 1;

int main() {
    std::cin >> N >> x;
    if (x == 1 || x == 2 * N - 1) {
        std::cout << "No" << '\n';
    } else {
        std::cout << "Yes" << '\n';
        a[N] = x;
        a[N - 1] = x - 1;
        a[N + 1] = x + 1;
        for (int i = 1; i < N - 1; i++, cur++) {
            if (cur == x - 1) cur = x + 2;
            a[i] = cur;
        }
        for (int i = N + 2; i <= 2 * N - 1; i++, cur++) {
            if (cur == x - 1) cur = x + 2;
            a[i] = cur;
        }
        for (int i = 1; i <= 2 * N - 1; i++) {
            std::cout << a[i] << '\n';
        }
    }
    return 0;
}