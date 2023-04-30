#include <iostream>

const int maxN = 2e4;

int n;
int p[maxN + 10];
int a[maxN + 10];
int b[maxN + 10];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i];
    for (int i = 1; i <= n; i++) a[p[i]] += i - 1;
    for (int i = 1; i <= n; i++) a[i] += i * maxN;
    for (int i = 1; i <= n; i++) b[n - i + 1] += i * maxN + 1;
    for (int i = 1; i <= n; i++) std::cout << a[i] << ' '; std::cout << '\n';
    for (int i = 1; i <= n; i++) std::cout << b[i] << ' ';
    return 0;
}