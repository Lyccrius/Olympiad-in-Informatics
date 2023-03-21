#include <iostream>

const int maxN = 1e5;

int N;
char a[maxN + 10];

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    if (a[1] != a[N]) {
        std::cout << 1;
    } else {
        bool ok = false;
        for (int i = 2; i < N - 1; i++) if (a[i] != a[1] && a[i + 1] != a[N]) ok = true;
        if (ok) {
            std::cout << 2;
        } else {
            std::cout << -1;
        }
    }
    return 0;
}