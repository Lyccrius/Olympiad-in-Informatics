#include <iostream>

typedef double dbl;

const int maxN = 250;
const int maxW = 1000;
const int inf = 1e9 + 10;
const dbl eps = 1e-6;

int n, W;
int w[maxN + 10], t[maxN + 10];
dbl f[maxW + 10];

bool check(dbl mid) {
    std::fill(f + 1, f + W + 1, -inf);
    for (int i = 1; i <= n; i++) {
        for (int j = W; j >= 0; j--) {
            int k = std::min(W, j + w[i]);
            f[k] = std::max(f[k], f[j] + t[i] - mid * w[i]);
        }
    }
    return f[W] > 0;
}

int main() {
    std::cin >> n >> W;
    for (int i = 1; i <= n; i++) std::cin >> w[i] >> t[i];
    dbl l = 0;
    dbl r = 1e9;
    while (r - l > eps) {
        dbl mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    std::cout << (int) (1000 * l) << '\n';
    return 0;
}