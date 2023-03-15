#include <iostream>
#include <algorithm>

const int maxN = 100;

int t;
int n;
int a[maxN + 10];
int top;
int tot;

void mian() {
    top = 0;
    tot = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) top = std::max(top, a[i]);
    for (int i = 1; i <= n; i++) tot += a[i];
    if (top > tot - top) {
        std::cout << "T" << '\n';
    } else {
        if (tot & 1) {
            std::cout << "T" << '\n';
        } else {
            std::cout << "HL" << '\n';
        }
    }
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}