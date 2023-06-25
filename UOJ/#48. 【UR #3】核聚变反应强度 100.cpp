#include <iostream>
#include <vector>

typedef long long lxl;
typedef std::vector<lxl> vlc;

const int maxN = 1e5;
const lxl maxA = 1e12;
const lxl sqrA = 1e6;

int n;
lxl a[maxN + 10];
int vis[sqrA + 10];
vlc prime;
vlc fac;

void init(lxl n) {
    for (lxl i = 2; i <= n; i++) {
        if (!vis[i]) prime.push_back(i);
        for (auto j : prime) {
            if (i * j > n) break;
            vis[i * j] = true;
            if (i % j == 0) break;
        }
    }
    return;
}

void sieve(lxl n) {
    for (auto i : prime) {
        if (i * i > n) break;
        if (n % i) continue;
        while (n % i == 0) n /= i;
        fac.push_back(i);
    }
    if (n > 1) fac.push_back(n);
    return;
}

lxl GCD(lxl a, lxl b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

int main() {
    init(sqrA);
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    sieve(a[1]);
    for (int i = 1; i <= n; i++) {
        lxl d = GCD(a[1], a[i]);
        if (d == 1) {
            std::cout << -1 << ' ';
            continue;
        }
        for (auto j : fac) {
            if (d % j == 0) {
                std::cout << d / j << ' ';
                break;
            }
        }
    }
    std::cout << '\n';
    return 0;
}