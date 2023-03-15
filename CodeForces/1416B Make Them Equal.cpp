#include <iostream>

const int maxN = 1e4;

int t;
int n;
int a[maxN + 10];
int sum;
int ave;

void init() {
    sum = 0;
    return;
}

void mian() {
    init();
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) sum += a[i];
    if (sum % n) {
        std::cout << -1 << '\n';
        return;
    }
    ave = sum / n;
    std::cout << 3 * (n - 1) << '\n';
    for (int i = 2; i <= n; i++) {
        int x = a[i] % i;
        std::cout << 1 << " " << i << " " << (i - x) % i << '\n';
        a[1] -= (i - x) % i;
        a[i] += (i - x) % i;
        std::cout << i << " " << 1 << " " << a[i] / i << '\n';
        a[1] += a[i];
        a[i] = 0; 
    }
    for(int i = 2; i <= n; i++) {
        std::cout << 1 << " " << i << " " << ave << '\n';
        a[1] -= ave;
        a[i] += ave;
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}