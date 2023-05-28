#include <iostream>
#include <iomanip>

typedef double dbl;

const int maxN = 1e5;

int n;
dbl p[maxN + 10];
dbl x1[maxN + 10];
dbl x2[maxN + 10];
dbl ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) {
        x1[i] = p[i] * (1 + x1[i - 1]);
        x2[i] = p[i] * (1 + x1[i - 1] * 2 + x2[i - 1]);
        ans += p[i] * (1 + x1[i - 1] * 3 + x2[i - 1] * 3);
    }
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(1) << ans << '\n';
    return 0;
}