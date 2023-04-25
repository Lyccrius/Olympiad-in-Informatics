#include <iostream>
#include <algorithm>

const int maxN = 2e5;

int t;
int n;
int a[maxN + 10];
int b[maxN + 10];

void mian() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    int l = 0;
    int r = 0;
    int mn = n + 1;
    int mx = 0;
    for (int i = 1; i <= n; i++) if (a[i] != b[i]) r = i;
    for (int i = n; i >= 1; i--) if (a[i] != b[i]) l = i;
    for (int i = l; i <= r; i++) mn = std::min(mn, a[i]);
    for (int i = l; i <= r; i++) mx = std::max(mx, a[i]);
    while (l > 1 && a[l - 1] <= mn) l--, mn = std::min(mn, a[l]);
    while (r < n && a[r + 1] >= mx) r++, mx = std::max(mx, a[r]);
    std::cout << l << ' ' << r << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}