#include <iostream>
#include <deque>
#include <map>

const int maxN = 100;

int t;
int n;
int b[maxN + 10];
int x[maxN + 10];
int m[maxN + 10];

void mian() {
    std::cin >> n;
    int zcnt = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
        if (b[i] > 0) zcnt++;
    }
    for (int i = 1; i <= zcnt; i++) x[i] = x[i - 1] + 1;
    for (int i = zcnt + 1; i <= n; i++) x[i] = x[i - 1] - 1;
    int fcnt = n - zcnt;
    for (int i = 1; i <= fcnt; i++) m[i * 2 - 1] = 1;
    for (int i = 1; i <= fcnt; i++) m[i * 2] = 0;
    for (int i = fcnt * 2 + 1; i <= n; i++) m[i] = m[i - 1] + 1;
    for (int i = 1; i <= n; i++) std::cout << x[i] << ' '; std::cout << '\n';
    for (int i = 1; i <= n; i++) std::cout << m[i] << ' '; std::cout << '\n';
    return;
}

int main() {
    std::cin >> t;
    while (t--) mian();
    return 0;
}