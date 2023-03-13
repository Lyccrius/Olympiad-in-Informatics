#include <iostream>
#include <algorithm>

const int maxN = 1e6;

int n;
int a[maxN + 10];
int b[maxN + 10];
int e[maxN + 10];
int ans;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = 1;
    for (int i = 1; i <= n; i++) e[i] = 1;
    for (int i = n; i >= 2; i--) if (a[i] > a[i - 1]) b[i - 1] = b[i] + 1;
    for (int i = 2; i <= n; i++) if (a[i] > a[i - 1]) e[i] = e[i - 1] + 1;
    for (int i = 1; i <= n; i++) ans = std::max(ans, b[i]);
    for (int i = 1; i <= n; i++) ans = std::max(ans, e[i]);
    for (int i = 2; i < n; i++) if (a[i - 1] + 1 <= a[i + 1] - 1) ans = std::max(ans, e[i - 1] + 1 + b[i + 1]);
    for (int i = 1; i < n; i++) ans = std::max(ans, b[i + 1] + 1);
    for (int i = n; i > 1; i--) ans = std::max(ans, e[i - 1] + 1);
    std::cout << ans;
    return 0;
}