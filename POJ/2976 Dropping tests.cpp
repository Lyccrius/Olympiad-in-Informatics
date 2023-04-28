#include <iostream>
#include <algorithm>

typedef double dbl;

const int maxN = 1000;
const dbl eps = 1e-6;

int n, k;
int a[maxN + 10];
int b[maxN + 10];
dbl c[maxN + 10];

bool check(dbl mid) {
    dbl s = 0;
    for (int i = 1; i <= n; i++) c[i] = a[i] - mid * b[i];
    std::sort(c + 1, c + n + 1);
    std::reverse(c + 1, c + n + 1);
    for (int i = 1; i <= n - k; i++) s += c[i];
    return s > 0;
}

void mian() {
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    dbl l = 0;
    dbl r = 1e9;
    while (r - l > eps) {
        dbl mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    std::cout << (int) (100 * l + 0.5) << '\n';
    return;
}

int main() {
    while (std::cin >> n >> k && n) mian();
    return 0;
}