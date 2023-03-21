#include <iostream>

const int maxN = 1e5;

int N, L;
int a[maxN + 10];
int cur;

int main() {
    std::cin >> N >> L;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) if (a[i] + a[i + 1] > a[cur] + a[cur + 1]) cur = i;
    if (a[cur] + a[cur + 1] >= L) {
        std::cout << "Possible" << '\n';
        for (int i = 1; i < cur; i++) std::cout << i << '\n';
        for (int i = N - 1; i > cur; i--) std::cout << i << '\n';
        std::cout << cur << '\n';
    } else {
        std::cout << "Impossible" << '\n';
    }
    return 0;
}