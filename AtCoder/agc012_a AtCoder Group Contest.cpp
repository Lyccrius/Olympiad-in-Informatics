#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 1e5;

int N;
lxl a[3 * maxN + 10];
lxl A;

int main() {
    std::cin >> N;
    for (int i = 1; i <= 3 * N; i++) std::cin >> a[i];
    std::sort(a + 1, a + 3 * N + 1);
    for (int i = N + 1; i <= 3 * N; i += 2) A += a[i];
    std::cout << A;
    return 0;
}