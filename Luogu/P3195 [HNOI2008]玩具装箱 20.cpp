#include <iostream>

typedef long long lxl;

const int maxN = 5e4;
const int maxL = 1e7;
const int maxC = 1e7;
const lxl inf = 1e18 + 10;

int n, L;
lxl c[maxN + 10];
lxl f[maxN + 10];

int main() {
    std::cin >> n >> L;
    for (int i = 1; i <= n; i++) std::cin >> c[i];
    for (int i = 1; i <= n; i++) c[i] += c[i - 1];
    for (int i = 1; i <= n; i++) {
        f[i] = inf;
        for (int j = 0; j < i; j++) {
            lxl t = i - (j + 1) + (c[i] - c[j]);
            f[i] = std::min(f[i], f[j] + (t - L) * (t - L));
        }
    }
    std::cout << f[n] << '\n';
    return 0;
}