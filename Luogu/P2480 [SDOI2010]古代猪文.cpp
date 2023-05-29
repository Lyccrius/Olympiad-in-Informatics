#include <iostream>
#include <vector>
#include <cmath>

typedef std::vector<int> vic;

const int mod = 999911659;

int n, g;
vic fac;
int A[40000];

int pow(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % p;
        a = 1ll * a * a % p;
        b = b / 2;
    }
    return ret;
}

int inv(int a, int p) {
    return pow(a, p - 2, p);
}

int C(int n, int m, int p) {
    if (m > n) return 0;
    return 1ll * A[n] * inv(A[m], p) % p * inv(A[n - m], p) % p;
}

int Lucas(int n, int m, int p) {
    if (m == 0) return 1;
    return 1ll * C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}

namespace crt {
    int n[5] = {0, 2, 3, 4679, 35617};
    int m[5];
    int a[5];

    int solve() {
        int ret = 0;
        for (int i = 1; i <= 4; i++) {
            m[i] = (mod - 1) / n[i];
            int t;
            t = (inv(m[i], n[i]) + n[i]) % n[i];
            ret = (1ll * ret + 1ll * m[i] * a[i] % (mod - 1) * t % (mod - 1)) % (mod - 1);
        }
        return ret;
    }
}

int main() {
    A[0] = 1;
    for (int i = 1; i <= crt::n[4]; i++) A[i] = 1ll * A[i - 1] * i % (mod - 1);
    std::cin >> n >> g;
    if (g == mod) {
        std::cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i * i <= n; i++) {
        if (n % i) continue;
        if (i * i != n) fac.push_back(n / i);
        fac.push_back(i);
    }
    for (int i = 1; i <= 4; i++) for (auto j : fac) crt::a[i] = (crt::a[i] + Lucas(n, j, crt::n[i])) % crt::n[i];
    std::cout << pow(g, crt::solve(), mod) << '\n';
    return 0;
}