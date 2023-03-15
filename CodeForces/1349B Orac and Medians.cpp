#include <iostream>

const int maxN = 1e5;

int t;
int n, k; int K;
int a[maxN + 10];

void mian() {
    std::cin >> n >> k; K = false;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) if (a[i] == k) K = true;
    if (!K) {
        std::cout << "no" << '\n';
        return;
    }
    if (n == 1) {
        std::cout << "yes" << '\n';
        return;
    }
    for (int i = 1; i < n; i++) if (a[i] >= k && a[i + 1] >= k) {std::cout << "yes" << '\n'; return;}
    for (int i = 2; i < n; i++) if (a[i - 1] >= k && a[i + 1] >= k) {std::cout << "yes" << '\n'; return;};
    std::cout << "no" << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}