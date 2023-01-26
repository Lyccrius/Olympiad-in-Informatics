#include <iostream>

const int maxN = 100;
const int maxH = 100;

int t;
int n;
int h[maxN + 10];

void mian() {
    std::cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) std::cin >> h[i];
    for (int i = 1; i <= n; i++) if (h[i] == 1) cnt++;
    std::cout << n - cnt / 2 << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}