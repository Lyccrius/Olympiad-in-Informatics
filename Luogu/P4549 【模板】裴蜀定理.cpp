#include <iostream>

const int maxN = 20;

int n;
int A[maxN + 10];
int ans;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> A[i];
    for (int i = 1; i <= n; i++) if (A[i] < 0) A[i] = - A[i];
    for (int i = 1; i <= n; i++) ans = gcd(ans, A[i]);
    std::cout << ans;
    return 0;
}