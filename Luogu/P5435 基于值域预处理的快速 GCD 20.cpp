#include <iostream>

const int maxN = 5000;
const int mod = 998244353;

int n;
int a[maxN + 10];
int b[maxN + 10];
int A[maxN + 10];

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) A[i] = (A[i] + 1ll * pow(i, j) * gcd(a[i], b[j]) % mod) % mod;
    for (int i = 1; i <= n; i++) std::cout << A[i] << '\n';
    return 0;
}