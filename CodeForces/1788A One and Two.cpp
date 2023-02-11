#include <iostream>

const int maxN = 1000;

int t;
int n;
int a[maxN + 10];
int p[maxN + 10];

void mian() {
    int cnt = 1;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1];
        if (a[i] == 2) p[i]++;
    }
    if (p[n] & 1) {
        std::cout << -1;
    } else {
        for (int i = 1; i <= n; i++) if (p[i] == p[n] / 2) {
            std::cout << i;
            break;
        }
    }
    std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}